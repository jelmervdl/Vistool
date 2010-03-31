#ifndef SVMCLASSIFIER_H
#define SVMCLASSIFIER_H

#include "classifier.h"
#include "svm.h"

class SVMClassifier : public Classifier{

 private:
  svm_problem *compileProblem(vector<DataPoint*> files);
  svm_parameter *getSVMParameters();
 public:
  using Classifier::train;
  vector<int> crossvalidation(vector<DataPoint> * files);
  vector<int> crossvalidation(vector<DataPoint*> files);
  void train(vector<DataPoint*> files);
  vector<int> classify(vector<DataPoint*> data_points);
  int classify(DataPoint * data_point);
}; 

#endif
