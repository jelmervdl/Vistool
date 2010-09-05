#include "segmentSVM.h"

using std::string;
using std::stringstream;
using std::vector;
using std::cout;
using std::endl;
using std::pair;

namespace vito{
namespace classification{

using features::FeatureExtractor;
using write::readDescriptor;

string SegmentSVM::get_name(){
  return "segmentSVM";
}

SegmentSVM::SegmentSVM(){
}

Matrix<Descriptor> SegmentSVM::extractKeyPoints(const Descriptor &descriptor){
  //cout << "original descriptor: " << endl;
  //descriptor.print();
  //cout << endl;
  Parameters *p = Parameters::getInstance();
  const int x_keypoints = p->getiParameter("sift_number_of_keypoints_x");
  const int y_keypoints = p->getiParameter("sift_number_of_keypoints_y");
  const int bins = p->getiParameter("sift_orientation_directions");
  Matrix< Descriptor > keypoints (x_keypoints, y_keypoints);
  for(int x = 0; x < x_keypoints; ++x){ 
    for(int y = 0; y < y_keypoints; ++y){
      keypoints.at(x,y).resize(bins);
      for(int bin = 0; bin < bins; ++bin){
	int index = bin + x * y_keypoints * bins + y * bins;
// 	cout << "x: " << x << " y: " << y << " bin: " 
// 	     << bin << " value: " << descriptor[index] 
//	     << " used index " << index << endl;
	keypoints.at(x,y)[bin] = descriptor[index];
      }
    }
  }
  return keypoints;
}

vector<Descriptor> SegmentSVM::getSubSquares(const Matrix<Descriptor> 
					     &keypoints){
  // cout << "extracting squares" << endl;
  vector<Descriptor> result;
  Parameters *p = Parameters::getInstance();
  const int square_size = 
    p->getiParameter("segmentsvm_subsquare_hist_count");
  const int width = keypoints.get_width();
  const int height = keypoints.get_height();
  //iterate regions
  for(int x = 0; x < width - square_size + 1; ++x){
    for(int y = 0; y < height - square_size + 1; ++y){
      Descriptor current;

      //iterate histograms to go into that region
      for(int square_x = 0; square_x < square_size; ++square_x)
	for(int square_y = 0; square_y < square_size; ++square_y){
// 	  cout << "x: " << x + square_x << " y: " << y + square_y << endl
// 	       << " descriptor: " << endl;
	  //keypoints.at(x + square_x, y + square_y).print();
	  //	  cout << endl;
	  current = current + keypoints.at(x + square_x, y + square_y);
	}
      //      cout << "pushing : " << endl;
      //current.print();
      result.push_back(current);
    }
  }
  return result;
}

vector<Descriptor> SegmentSVM::getSubregions(const Descriptor &descriptor){
  Parameters *p = Parameters::getInstance();
  vector<Descriptor> subregions;
  Matrix<Descriptor> keypoints = extractKeyPoints(descriptor);
  const int segment_type = p->getiParameter("segmentsvm_segment_type");
  if(segment_type == 0)
    subregions = getSubSquares(keypoints);
  return subregions;
}

svm_problem * SegmentSVM::compileSegmentProblem(const vector<DataPoint*>
					        &data_points){
  Descriptor sample;
  readDescriptor(&sample,
		 FeatureExtractor::getInstance()->
		 getCurrentDescriptorLocation(*data_points[0])); 
  vector<Descriptor> sample_desc = getSubregions(sample);
  svm_problem *problem_ = new svm_problem;
  svm_problem &problem = *problem_;
  const int kNodesPerFile = sample_desc.size();
  const int kNodes = data_points.size() * kNodesPerFile;
  const int descriptor_length = sample_desc[0].size();
  problem.l = kNodes;
  problem.y = new double[kNodes];
  problem.x = new svm_node*[kNodes];
  for(int dp_i = 0; dp_i < (int) data_points.size(); ++dp_i){
    DataPoint &data_point = *data_points[dp_i];
    Descriptor original_descriptor;
    readDescriptor(&original_descriptor,
		   FeatureExtractor::getInstance()->
		   getCurrentDescriptorLocation(data_point));
    vector<Descriptor> regions = getSubregions(original_descriptor);
    for(int region_i = 0; region_i < (int) regions.size(); ++region_i){
      const Descriptor &region = regions[region_i];
      const int node_number = region_i + dp_i * kNodesPerFile;
      problem.y[node_number] = (double) data_point.get_label();
      problem.x[node_number] = new svm_node[ descriptor_length + 1];
      fillNodes(problem.x[node_number], region);
    }
      
  }
  return problem_;
}

void SegmentSVM::fillNodes(svm_node* &nodes, const Descriptor &descriptor){
  //  cout << "the descriptor" << endl;
  //descriptor.print();
  //  cout << "end of descriptor" << endl;
  const int descriptor_length = descriptor.size();
  nodes = new svm_node[ descriptor_length + 1];
  for(int desc_i = 0; desc_i < descriptor_length; ++desc_i){
    //    cout << descriptor[desc_i] << " is the descriptor val " << endl;
    nodes[desc_i].value = descriptor[desc_i];
    nodes[desc_i].index = desc_i;
  }
  nodes[descriptor_length].index = -1;
  nodes[descriptor_length].value = 0.0;
}

void SegmentSVM::train(vector<DataPoint*> data_points){
  Parameters *p = Parameters::getInstance();
  p->requireOnlySift();
  svm_parameter *parameters = getSVMParameters();
  svm_problem *problem = compileSegmentProblem(data_points);
  //print::print_svm_problem(problem);
  //print::print_svm_problem(problem);
  svm_model *model = svm_train(problem, parameters);
  svm_save_model("model.svm", model);
}


vector<int> SegmentSVM::classify(vector<DataPoint*> data_points){
  svm_model *model =  svm_load_model("model.svm");
  vector<int> results(data_points.size());
  for(int i = 0; i < (int) data_points.size(); ++i)
    results[i] = classify(data_points[i], model);
  return results;
}

int SegmentSVM::classify(DataPoint *data_point){
  svm_model *model =  svm_load_model("model.svm");
  return classify(data_point, model);
}

bool sorter(pair<double, string> a, pair<double, string> b){
  return a.first > b.first;
}

int SegmentSVM::classify(DataPoint *data_point, svm_model * model){
  //cout << "actual: " << data_point->get_label() << endl << endl;
  Descriptor desc;
  readDescriptor(&desc,
		 FeatureExtractor::getInstance()->
		 getCurrentDescriptorLocation(*data_point));
  vector<Descriptor> regions = getSubregions(desc);
  vector<float> totals (6);
  vector<pair<double, string> > sortem;
  double max_abs = 0;
  int final_answer;
  for(int i = 0; i < (int) regions.size(); ++i){
    stringstream ss;
    svm_node *node;
    fillNodes(node, regions[i]);
    double answer = svm_predict(model, node);
    vector<double> values = getValues(node, model);
    double abs_sum =0 , max = 0;
    for(int i = 0; i < (int) values.size(); ++i){
      //cout << values[i] << " ";
      ss << values[i] << " ";
      totals[i] += values[i];
      abs_sum += std::fabs(values[i]);
      if(values[i] > max){
	max = values[i];
      }
    }
    //cout << " abs: " << abs_sum << " max: " << max << endl;
    ss << " abs: " << abs_sum << " max: " << max << endl;
    sortem.push_back(pair<double, string>(abs_sum, ss.str()));
    if(abs_sum > max_abs){
      max_abs = abs_sum;
      final_answer = answer;
    }
  }
  //  std::sort(sortem.begin(), sortem.end(), sorter); 
  //cout << "totals: ";
  //for(int i = 0; i < (int) totals.size(); ++i)
  //cout << totals[i] << " ";
  //  cout << endl << endl;
  //  cout << "size of the sortum: " << sortem.size() << endl;
  //  for(int i = 0; i < (int) sortem.size(); ++i)
  //cout << "::" << sortem[i].second;
  return final_answer;
}

}}
