#include "svmclassifier.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace vito{
namespace classification{

using features::FeatureExtractor;
using write::readDescriptor;

string SVMClassifier::get_name(){
  return "SVM";
}

vector<int> SVMClassifier::crossvalidation(vector<DataPoint> * files){
  return Classifier::crossvalidation(files);
}

vector<int> SVMClassifier::crossvalidation(vector<DataPoint*> files){
  svm_problem * problem = compileProblem(files);
  svm_parameter * parameter = getSVMParameters();
  double result[problem->l];
  svm_cross_validation(problem, parameter, 10, result);
  vector<int> classification(problem->l);
  for(size_t i = 0; i < (size_t) problem->l; ++i){
    classification[i] = (int) result[i];
  }
  return classification;
}

void SVMClassifier::train(vector<DataPoint*> files){
  svm_problem   *problem = compileProblem(files);
  svm_parameter *parameter = getSVMParameters();
  svm_model     *model = svm_train(problem, parameter);
  svm_save_model("model.svm", model);
  svm_destroy_model(model);
  svm_destroy_param(parameter);
}

svm_problem *SVMClassifier::compileProblem(vector<DataPoint*> files){
  const int& n_datapoints = files.size();
  if(n_datapoints < 1){
    printf("dude.. can't train on nothing...\n");
    return NULL;
  }
  svm_problem *problem_ = new svm_problem;
  svm_problem &problem = *problem_;
  problem.l = 0;
  problem.y = new double[n_datapoints]; // labels
  problem.x = new svm_node*[n_datapoints]; // datapoints
  for(size_t dp_index = 0; (int) dp_index < n_datapoints; ++dp_index){
    const DataPoint& current_datapoint = *files[dp_index];
    addDataPointToProblem(problem, current_datapoint);
  }
  return &problem;
}

double SVMClassifier::dataPointLabel(const DataPoint &datapoint){
  return datapoint.get_label();
}

void SVMClassifier::addDataPointToProblem(svm_problem &problem, 
					  const DataPoint &current_datapoint){
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  vector<float> descriptor;
  readDescriptor(&descriptor,
		 fe->getCurrentDescriptorLocation(current_datapoint));
  const int &descriptor_length = descriptor.size();
  const int dp_index = problem.l;
  problem.l++;

  problem.y[dp_index] = (double) dataPointLabel(current_datapoint);
  problem.x[dp_index] = new svm_node[descriptor_length + 1];
  svm_node* &current_descriptor_nodes = problem.x[dp_index];
  for(int descr_part = 0; descr_part < descriptor_length; ++descr_part){
    svm_node &current_node = current_descriptor_nodes[descr_part];
    current_node.index = descr_part; // set the feature index
    current_node.value = descriptor[descr_part]; // set feature value
  }
  svm_node &last_node = problem.x[dp_index][descriptor_length];
  last_node.index = -1;
  last_node.value = 0.0;
}

svm_parameter *SVMClassifier::getSVMParameters(){
  Parameters &p = *Parameters::getInstance();
  svm_parameter *newpar = new svm_parameter;
  svm_parameter &multi_svm_par = *newpar;
  multi_svm_par.svm_type =  C_SVC;
  multi_svm_par.kernel_type = RBF;
  multi_svm_par.degree = p.getiParameter("svm_degree");
  multi_svm_par.gamma = p.getfParameter("svm_gamma");	
  multi_svm_par.coef0 = p.getfParameter("svm_coef0");

  multi_svm_par.cache_size = 1024;
  multi_svm_par.eps = p.getfParameter("svm_eps");
  multi_svm_par.C = p.getfParameter("svm_C");
  multi_svm_par.nr_weight = p.getiParameter("svm_nr_weight");
  multi_svm_par.weight_label = 0;
  multi_svm_par.weight = 0;
  multi_svm_par.nu = p.getfParameter("svm_nu");
  multi_svm_par.p = p.getfParameter("svm_p");
  multi_svm_par.shrinking = p.getiParameter("svm_shrinking");
  multi_svm_par.probability = p.getiParameter("svm_probabiity");
  return newpar;
}

vector<int> SVMClassifier::classify(vector<DataPoint*> data_points){
  svm_model *model = svm_load_model("model.svm");
  vector<int> results(data_points.size());
  for(int i = 0; i < (int) data_points.size(); ++i)
    results[i] = classify(data_points[i], model);
  return results;
}

int SVMClassifier::classify(DataPoint *data_point){
  svm_model *model = svm_load_model("model.svm");
  return classify(data_point, model);
}

vector<double> SVMClassifier::getValues(svm_node *nodes,
					svm_model *model){
  const int nr_classes = svm_get_nr_class(model);
  const int nr_values = (nr_classes * (nr_classes + 1) ) / 2;
  double *values = new double[ nr_values ];
  for(int i = 0; i < nr_values; ++i)
    values[i] = 0.0;
  svm_predict_values(model, nodes, values);
  vector<double> value_per_class(nr_classes);
  int index = 0;
  for(int i = 0; i < nr_classes; ++i)
    for(int j = i + 1; j < nr_classes; ++j){
      cout << "waarde van value_ " << values[index] << endl;
      value_per_class[i] += values[index];
      value_per_class[j] -= values[index];
      index++;
    }
  delete values;
  return value_per_class;
}

int SVMClassifier::classify(DataPoint *data_point, svm_model *model){
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  vector<float> descriptor;
  readDescriptor(&descriptor, 
		 fe->getCurrentDescriptorLocation(*data_point));  
  svm_node *nodes = new svm_node[descriptor.size() + 1];
  for(int i = 0; i < (int) descriptor.size(); ++i){
    nodes[i].value = descriptor[i];
    nodes[i].index = i;
  }
  nodes[descriptor.size()].value = 0.0;
  nodes[descriptor.size()].index = -1; 
  double result = svm_predict(model, nodes);
  cout << "result: " << result << endl
       << "actual: " << data_point->get_label() << endl;
  vector<double> value_per_class = getValues(nodes, model);
  
  for(vector<double>::iterator it = value_per_class.begin();
      it != value_per_class.end();
      ++it)
    cout << *it << " ";
  cout << endl;
  
  return result;
}

}}
