#include "svmclassifier.h"


using std::vector;
using std::cout;
using std::endl;

namespace vito{
namespace classification{

using features::FeatureExtractor;

using write::readDescriptor;

vector<int> SVMClassifier::crossvalidation(vector<DataPoint> * files){
  return crossvalidation( ptr::ptrDeMorgan<DataPoint>(files) );
}

vector<int> SVMClassifier::crossvalidation(vector<DataPoint*> files){
  svm_problem * problem = compileProblem(files);
  cout << endl;
  svm_parameter * parameter = getSVMParameters();
  //svm_model * model =  svm_train(problem, parameter);
  double result[problem->l];
  svm_cross_validation(problem, parameter, 10, result);
  vector<int> classification(problem->l);
  for(size_t i = 0; i < (size_t) problem->l; ++i){
    //    printf("at %d:%d\n" 
    classification[i] = (int) result[i];
  }
  return classification;
}

void SVMClassifier::train(vector<DataPoint*> files){
}

svm_problem *SVMClassifier::compileProblem(vector<DataPoint*> files){
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  const int& n_datapoints = files.size();

  if(n_datapoints < 1){
    printf("dude.. can't train on nothing...\n");
    return NULL;
  }
  vector<float> sample;
  readDescriptor(&sample, fe->getCurrentDescriptorLocation(*files.at(0)));
  const int &descriptor_length = sample.size();
  for(int i = 0; i < descriptor_length; ++i)
    printf("svm find at place %d to be %.02f\n", i, sample[i]);
  //reserve a problem according to the sample
  svm_problem *problem_ = new svm_problem;
  svm_problem &problem = *problem_;
  problem.l = n_datapoints;
  problem.y = new double[n_datapoints]; // labels
  problem.x = new svm_node*[n_datapoints]; // datapoints
  // arrange libsvm nodes
  for(size_t dp_index = 0; (int) dp_index < n_datapoints; ++dp_index){
    const DataPoint& current_datapoint = *files[dp_index];

    problem.y[dp_index] = (double) current_datapoint.get_label(); // set the label
    problem.x[dp_index] = new svm_node[descriptor_length + 1];

    svm_node* &current_descriptor_nodes = problem.x[dp_index];

    vector<float> descriptor;
    readDescriptor(&descriptor,fe->getCurrentDescriptorLocation(current_datapoint));
    for(size_t descr_part = 0; (int) descr_part < descriptor_length; ++descr_part){
      svm_node &current_node = current_descriptor_nodes[descr_part];
      current_node.index = descr_part; // set the feature index
      current_node.value = descriptor[descr_part]; // set feature value
    }
    svm_node &last_node = problem.x[dp_index][descriptor_length];
    last_node.index = -1;
    last_node.value = 0.0;
  }
  return &problem;
}

svm_parameter *SVMClassifier::getSVMParameters(){
  Parameters &p = *Parameters::getInstance();
  svm_parameter *newpar = new svm_parameter;
  svm_parameter &multi_svm_par = *newpar;
  multi_svm_par.svm_type =  C_SVC;
  multi_svm_par.kernel_type = POLY;
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
  //STUB
  vector<int> results(data_points.size());
  return results;
}

int SVMClassifier::classify(DataPoint * data_point){
  //STUB
  return 0;
}

}}
