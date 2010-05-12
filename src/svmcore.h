#ifndef SVMCORE
#define SVMCORE

#include "svm.h"

namespace vito{
namespace classification{

class SVMProblem : public svm_problem {
public:
  ~SVMProblem();
}; 

class SVMParameter : public svm_parameter {
public:
  SVMParameter();
  ~SVMParameter();
};


class SVMModel{
public:
  svm_model * model;
  ~SVMModel();
};

}}

#endif
