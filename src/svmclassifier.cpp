#include "svmclassifier.h"

using std::vector;
using std::cout;
using std::endl;


vector<int> SVMClassifier::crossvalidation(vector<DataPoint> * files){
  cout << " joer dan? " << endl;
  return crossvalidation( VisionCore::ptrDeMorgan<DataPoint>(files) );
}

vector<int> SVMClassifier::crossvalidation(vector<DataPoint*> files){
  cout << "ben ik hier? " << endl;
  svm_problem * problem = compileProblem(files);
  cout << endl;
  svm_parameter * parameter = getSVMParameters();
  cout << "parameters created" << endl;
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
  cout << "what about here" << endl;
  const int& n_datapoints = files.size();

  if(n_datapoints < 1){
    printf("dude.. can't train on nothing...\n");
    return NULL;
  }
  vector<float> sample;
  readDescriptor(&sample, files.at(0)->getDescriptorURL());
  const int &descriptor_length = sample.size();
  
  //reserve a problem according to the sample
  cout << "nothing has been allocated " << endl;
  svm_problem *problem_ = new svm_problem;
  svm_problem &problem = *problem_;
  cout << "problem alloc" << endl;
  problem.l = n_datapoints;
  problem.y = new double[n_datapoints]; // labels
  problem.x = new svm_node*[n_datapoints]; // datapoints
  cout << "here?" << endl;
  // arrange libsvm nodes
  for(size_t dp_index = 0; (int) dp_index < n_datapoints; ++dp_index){
    const DataPoint& current_datapoint = *files[dp_index];

    problem.y[dp_index] = (double) current_datapoint.getLabel(); // set the label
    problem.x[dp_index] = new svm_node[descriptor_length + 1];

    svm_node* &current_descriptor_nodes = problem.x[dp_index];

    vector<float> descriptor;
    readDescriptor(&descriptor, current_datapoint.getDescriptorURL());

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
  svm_parameter * newpar = new svm_parameter;
  svm_parameter &multi_svm_par = *newpar;
  multi_svm_par.svm_type =  C_SVC;
  multi_svm_par.kernel_type = POLY;
  multi_svm_par.degree = 7;	/* for poly */
  multi_svm_par.gamma = 55.5;	/* for poly/rbf/sigmoid */
  multi_svm_par.coef0 = 15.0;	/* for poly/sigmoid */

  /* these are for training only */
  multi_svm_par.cache_size = 1024; /* in MB */
  multi_svm_par.eps = 1e-3;	/* stopping criteria */
  multi_svm_par.C = 20;	/* for C_SVC, EPSILON_SVR, and NU_SVR */
  multi_svm_par.nr_weight = 0;		/* for C_SVC */
  multi_svm_par.weight_label = 0;	/* for C_SVC */
  multi_svm_par.weight = 0;		/* for C_SVC */
  multi_svm_par.nu = 0.0;	/* for NU_SVC, ONE_CLASS, and NU_SVR */
  multi_svm_par.p = 0.0;	/* for EPSILON_SVR */
  multi_svm_par.shrinking = 1.0;	/* use the shrinking heuristics */
  multi_svm_par.probability = 0.5; /* do probability estimates */                    
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
