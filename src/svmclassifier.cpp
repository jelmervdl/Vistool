#include "svmclassifier.h"

void SVMClassifier::train(vector<DataPoint*> files){
  svm_problem * problem = compileProblem(files);
  svm_parameter * parameter = getSVMParameters();
  //struct svm_model model =  *svm_train(problem, parameter);
}

svm_problem *SVMClassifier::compileProblem(vector<DataPoint*> files){
  const int& n_datapoints = files.size();

  if(n_datapoints < 0){
    printf("dude.. can't train on nothing...\n");
    return NULL;
  }
  vector<float> sample;
  readDescriptor(&sample, files.at(0)->getDescriptorURL());
  const int &descriptor_length = sample.size();
  
  //reserve a problem according to the sample
  svm_problem &problem = *new svm_problem;
  problem.l = n_datapoints;
  problem.y = new double[n_datapoints]; // labels
  problem.x = new svm_node*[n_datapoints]; // datapoints

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
  multi_svm_par.degree = 3;	/* for poly */
  multi_svm_par.gamma = 0.5;	/* for poly/rbf/sigmoid */
  multi_svm_par.coef0 = 5.0;	/* for poly/sigmoid */

  /* these are for training only */
  multi_svm_par.cache_size = 1024; /* in MB */
  multi_svm_par.eps = 1e-3;	/* stopping criteria */
  multi_svm_par.C = 1;	/* for C_SVC, EPSILON_SVR, and NU_SVR */
  multi_svm_par.nr_weight = 0;		/* for C_SVC */
  multi_svm_par.weight_label = 0;	/* for C_SVC */
  multi_svm_par.weight = 0;		/* for C_SVC */
  multi_svm_par.nu = 0.0;	/* for NU_SVC, ONE_CLASS, and NU_SVR */
  multi_svm_par.p = 0.0;	/* for EPSILON_SVR */
  multi_svm_par.shrinking = 1.0;	/* use the shrinking heuristics */
  multi_svm_par.probability = 0.0; /* do probability estimates */                    
  return newpar;
}
