#include "oneClassSVM.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;


namespace vito{
namespace classification{

void OneClassSVM::train(vector<DataPoint*> files){
  vector<DataPoint*> res;
  for(vector<DataPoint*>::iterator it = files.begin();
      it != files.end();
      ++it)
    if((int)(*it)->get_label() == truth_label)
      res.push_back(*it);
  return SVMClassifier::train(res);
}

OneClassSVM::OneClassSVM() : truth_label(0){
};

OneClassSVM::OneClassSVM(int truth) : truth_label(truth){
}

double OneClassSVM::dataPointLabel(const DataPoint &datapoint){
  return truth_label;
}
  

string OneClassSVM::get_name(){
  return "one class svm";
}

svm_parameter *OneClassSVM::getSVMParameters(){
  Parameters &p = *Parameters::getInstance();
  svm_parameter *newpar = new_svm_parameters();
  svm_parameter &multi_svm_par = *newpar;
  multi_svm_par.svm_type =  ONE_CLASS;
  multi_svm_par.kernel_type = RBF;
  multi_svm_par.gamma = p.getfParameter("one_class_gamma");//25.0 / 514.0;//p.getfParameter("svm_gamma");	


  multi_svm_par.cache_size = 1024;
  multi_svm_par.eps = 0.001;//p.getfParameter("svm_eps");
  multi_svm_par.nu = p.getfParameter("one_class_nu"); //0.125; // p.getfParameter("svm_nu");

  return newpar;
}

vector<double> OneClassSVM::getValues(svm_node *nodes,
				      svm_model *model){
  double value;
  svm_predict_values(model, nodes, &value);
  vector<double> rets(1);
  rets.push_back(value);
  return rets;
}

vector<double> OneClassSVM::getValue(DataPoint *dp){
  svm_model *model;
  model = svm_load_model("model.svm");
  return getValue(dp, model);
}

vector<double> OneClassSVM::getValue(DataPoint *dp, svm_model *model){
  svm_node * nodes = constructNode(dp);
  return getValues(nodes, model);
}

void OneClassSVM::set_truth_label(const int i ){
  truth_label = i;
}

/*
int OneClassSVM::classify(DataPoint *data_point, svm_model *model){
  int res = SVMClassifier::classify(data_point, model);
  cout << "original results: " <<  res;
  int output;
  if(res == 1)
    output = truth_label;
  if(res == -1) 
    output = -1;
  cout << " with output " << output << endl;
  return res;
}
*/
bool OneClassSVM::single_class(){
  return true;
}

}}
