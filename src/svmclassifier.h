#ifndef SVMCLASSIFIER_H
#define SVMCLASSIFIER_H

#include "classifier.h"
#include "svm.h"

class SVMClassifier : public Classifier
{
 private:
  svm_problem *compileProblem(vector<DataPoint*> files);
  svm_parameter *getSVMParameters();
 public:
  void train(vector<DataPoint*> files);

}; 

#endif
