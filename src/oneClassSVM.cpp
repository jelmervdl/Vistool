#include "oneClassSVM.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;


namespace vito{
namespace classification{

OneClassSVM::OneClassSVM(int truth) : truth_label(truth){
}

double OneClassSVM::dataPointLabel(const DataPoint &datapoint){
  //cout << "ok : " <<  2 * (datapoint.get_label() == truth_label) - 1<< endl;
  //return  2 * (datapoint.get_label() == truth_label) - 1;
  return 0;
}
  

string OneClassSVM::get_name(){
  return "one class svm";
}

svm_parameter *OneClassSVM::getSVMParameters(){
  Parameters &p = *Parameters::getInstance();
  svm_parameter *newpar = new svm_parameter;
  svm_parameter &multi_svm_par = *newpar;
  multi_svm_par.svm_type =  ONE_CLASS;
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

vector<double> OneClassSVM::getValues(svm_node *nodes,
					svm_model *model){
  double * value = new double;
  svm_predict_values(model, nodes, value);
  cout << endl << *value << endl;
  vector<double> rets(1);
  rets.push_back(*value);
  return rets;
}

}}
