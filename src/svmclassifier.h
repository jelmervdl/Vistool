#ifndef SVMCLASSIFIER_H
#define SVMCLASSIFIER_H

#include "classifier.h"
#include "svm.h"



class SVMClassifier : public Classifier{
  using Classifier::train;
  using Classifier::crossvalidation;
 private:
  svm_problem *compileProblem(std::vector<DataPoint*> files);
  svm_parameter *getSVMParameters();
 public:
  std::vector<int> crossvalidation(std::vector<DataPoint> * files);
  std::vector<int> crossvalidation(std::vector<DataPoint*> files);
  void train(std::vector<DataPoint*> files);
  std::vector<int> classify(std::vector<DataPoint*> data_points);
  int classify(DataPoint * data_point);
}; 

#endif
