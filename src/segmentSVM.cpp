#include "segmentSVM.h"

using std::vector;
using std::cout;
using std::endl;

namespace vito{
namespace classification{

using features::FeatureExtractor;
using write::readDescriptor;

SegmentSVM::SegmentSVM(){
}

Matrix<Descriptor> SegmentSVM::extractKeyPoints(const Descriptor &descriptor){
  Parameters *p = Parameters::getInstance();
  const int x_keypoints = p->getiParameter("sift_number_of_keypoints_x");
  const int y_keypoints = p->getiParameter("sift_number_of_keypoints_y");
  const int bins = p->getiParameter("sift_orientation_directions");
  Matrix< Descriptor > keypoints (x_keypoints, y_keypoints);
  for(int x = 0; x < x_keypoints; ++x){ 
    for(int y = 0; y < y_keypoints; ++y){
      keypoints.at(x,y).resize(bins);
      for(int bin = 0; bin < bins; ++bin){
	keypoints.at(x,y)[bin] = descriptor[x * bins + y];
      }
    }
  }
  return keypoints;
}

vector<Descriptor> SegmentSVM::getSubSquares(const Matrix<Descriptor> 
					     &keypoints){
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
	  current = current + keypoints.at(x + square_x, y + square_y);
	}
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
  const int descriptor_length = descriptor.size();
  nodes = new svm_node[ descriptor_length + 1];
  for(int desc_i = 0; desc_i < descriptor_length; ++desc_i){
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
  svm_model *model = svm_train(problem, parameters);
}

vector<int> SegmentSVM::crossvalidation(vector<DataPoint> *data_points){
  vector<int> results;
  return results;
}


vector<int> SegmentSVM::classify(vector<DataPoint*> data_points){
  vector<int> results(data_points.size());
  for(int i = 0; i < (int) data_points.size(); ++i){
    results[i] = classify(data_points[i]);
  }
  return results;
}

int SegmentSVM::classify(DataPoint *data_point){
  Descriptor desc;
  readDescriptor(&desc,
		 FeatureExtractor::getInstance()->
		 getCurrentDescriptorLocation(*data_point));
  vector<Descriptor> regions = getSubregions(desc);
  cout << "subregion has " << regions.size()  << endl;
}

}}
