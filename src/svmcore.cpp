#include "svmcore.h"

namespace vito{
namespace classification{

SVMProblem::~SVMProblem(){
  delete [] y;
  y = 0;
  for(int i = 0; i < l; ++i){
    delete [] x[i];
    x[i] = 0;
  }
  delete [] x;
  x = 0;
}

SVMParameter::SVMParameter(){
  svm_type = 0;
  kernel_type = 2;
  degree = 3;
  gamma = 1;
  coef0 = 0;
  cache_size = 100;
  eps = 0.001;
  C = 1;
  nr_weight = 0;
  weight_label = 0;
  weight = 0;
  nu = 0.25;
  p = 0;
  shrinking = 0;
  probability = 0;  
}

SVMParameter::~SVMParameter(){
  svm_destroy_param(this);
}


SVMModel::~SVMModel(){
  svm_destroy_model(model);
}

}}
