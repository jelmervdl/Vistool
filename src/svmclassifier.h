#ifndef SVMCLASSIFIER_H
#define SVMCLASSIFIER_H

#include "classifier.h"
#include "svm.h"

namespace vito{
namespace classification{


class SVMClassifier : public Classifier{
  using Classifier::train;
  using Classifier::crossvalidation;
 private:
  // compile a set of datapoints into a problem
  svm_problem     *compileProblem(std::vector<DataPoint*> files);

  // get the svm parameters
  svm_parameter   *getSVMParameters();

 public:
  // helper function for real crossvalidation function
  std::vector<int> crossvalidation(std::vector<DataPoint> * files);

  // crossvalidation using svm's built in cross validator (saves
  // filesaving)
  std::vector<int> crossvalidation(std::vector<DataPoint*> files);

  // train the svm
  void             train(std::vector<DataPoint*> files);

  // classify a set of datapoints
  std::vector<int> classify(std::vector<DataPoint*> data_points);

  // classify a single point
  int              classify(DataPoint * data_point);

  // classify a single point given a model
  int              classify(DataPoint *data_point, svm_model *model);
}; 

}}

#endif
