#include "svmclassifier.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace vito{
namespace classification{

using features::FeatureExtractor;
using write::readDescriptor;


SVMClassifier::~SVMClassifier(){
  if(model != 0){
    svm_free_and_destroy_model(&model);
    model = 0;
  }
  if(prblm != 0){
    svm_destroy_problem(prblm);
    prblm = 0;
  }
}

void svm_destroy_problem(svm_problem *problem){
  delete [] problem->y;
  problem->y = 0;
  for(int i = 0; i < problem->l; ++i){
    delete [] problem->x[i];
    problem->x[i] = 0;
  }
  delete [] problem->x;
  problem->x = 0;
}


string SVMClassifier::get_name(){
  return "SVM";
}

void SVMClassifier::train(const ExampleCollection &examples){
  cout << "training" << endl;
  cout << "problem is: " << prblm << endl;
  cout << "model is: " << model << endl;
  if(model != 0){
    svm_free_and_destroy_model(&model);
    model = 0;
  }
  if(prblm != 0){
    cout << "removing problem" << endl;
    svm_destroy_problem(prblm);
    prblm = 0;
  }
  cout << "training on " << examples.size() << " examples" << endl;
  
  prblm = compileProblem(examples);
  //print::print_svm_problem(problem);
  svm_parameter *parameter = getSVMParameters();
  model = svm_train(prblm, parameter);
  cout << "done training" << endl;
}

svm_problem *SVMClassifier::compileProblem(const ExampleCollection &examples){
  // check if there are 1 or more examples to train on
  const int& kExamples = examples.size();
  if(kExamples < 1){
    printf("dude.. can't train on nothing...\n");
    return NULL;
  }
  svm_problem *problem_ = new svm_problem;
  svm_problem &problem = *problem_;
  problem.l = 0; 
  problem.y = new double[kExamples]; // labels
  problem.x = new svm_node*[kExamples]; // datapoints
  // add every example to our newly allocated svm_problem
  for(size_t i = 0; (int) i < kExamples; ++i)
    addExampleToProblem(problem, examples[i]);
  return &problem;
}

double SVMClassifier::dataPointLabel(const DataPoint &datapoint){
  return datapoint.get_label();
}

void SVMClassifier::addExampleToProblem(svm_problem &problem, 
					const Example &example){
  const int &descriptor_length = example.size();
  const int i = problem.l;
  problem.y[i] = (double) example.get_label();
  problem.x[i] = new svm_node[descriptor_length + 1];
  svm_node* &current_descriptor_nodes = problem.x[i];
  for(int v = 0; v < descriptor_length; ++v){ // v is for value
    svm_node &current_node = current_descriptor_nodes[v];
    current_node.index = v; // set the feature index
    current_node.value = example[v]; // set feature value
  }
  svm_node &last_node = problem.x[i][descriptor_length];
  last_node.index = -1;
  last_node.value = 0.0;
  problem.l++;
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
      //cout << "waarde van value_ " << values[index] << endl;
      value_per_class[i] += values[index];
      value_per_class[j] -= values[index];
      index++;
    }
  delete values;
  return value_per_class;
}

svm_node* SVMClassifier::constructNode(const Descriptor &descriptor){
  svm_node *nodes = new svm_node[descriptor.size() + 1];
  for(int i = 0; i < (int) descriptor.size(); ++i){
    nodes[i].value = descriptor[i];
    nodes[i].index = i;
  }
  nodes[descriptor.size()].value = 0.0;
  nodes[descriptor.size()].index = -1; 
  //delete [] nodes;
  return nodes;
}

int SVMClassifier::classify(const Descriptor &descriptor){
  return classify(descriptor, model);
}

int SVMClassifier::classify(const Descriptor &descriptor, svm_model *model){
  svm_node *nodes = constructNode(descriptor);
  //print::print_svm_nodes(nodes, descriptor.size());
  double   result = svm_predict(model, nodes);
  //vector<double> value_per_class = getValues(nodes, model);
  delete [] nodes;
  return result;
}

svm_parameter * SVMClassifier::new_svm_parameters(){
  svm_parameter *newsvm =  new svm_parameter;
  newsvm->svm_type = C_SVC;
  newsvm->kernel_type = RBF;
  newsvm->degree = 0;	/* for poly */
  newsvm->gamma = 0;	/* for poly/rbf/sigmoid */
  newsvm->coef0 = 0;	/* for poly/sigmoid */

	/* these are for training only */
  newsvm->cache_size = 1024; /* in MB */
  newsvm->eps = 0;	/* stopping criteria */
  newsvm->C = 0;	/* for C_SVC, EPSILON_SVR and NU_SVR */
  newsvm->nr_weight = 0;		/* for C_SVC */
  newsvm->weight_label = 0;	/* for C_SVC */
  newsvm->weight = 0;		/* for C_SVC */
  newsvm->nu = 0;	/* for NU_SVC, ONE_CLASS, and NU_SVR */
  newsvm->p = 0;	/* for EPSILON_SVR */
  newsvm->shrinking = 0;	/* use the shrinking heuristics */
  newsvm->probability = 0; /* do probability estimates */
  return newsvm;
};

}}
