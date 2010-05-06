#ifndef SVMCLASSIFIER_H
#define SVMCLASSIFIER_H

#include "classifier.h"
#include "svm.h"

namespace vito{
namespace classification{

class SVMClassifier : public Classifier{
  using Classifier::train;
  using Classifier::crossvalidation;

 protected:
  virtual std::string         get_name();

  virtual double              dataPointLabel(const DataPoint &datapoint);
  // compile a set of datapoints into a problem
  virtual svm_problem        *compileProblem(std::vector<DataPoint*> files);

  // get the svm parameters
  virtual svm_parameter       *getSVMParameters();

  void                         addDataPointToProblem(svm_problem &problem, 
						     const DataPoint &dp);

 public:
  // helper function for real crossvalidation function
  virtual std::vector<int>     crossvalidation(std::vector<DataPoint> * files);

  // crossvalidation using svm's built in cross validator (saves
  // filesaving)
  virtual std::vector<int>     crossvalidation(std::vector<DataPoint*> files);

  // train the svm
  virtual void                 train(std::vector<DataPoint*> files);

  // classify a set of datapoints
  virtual   std::vector<int>   classify(std::vector<DataPoint*> data_points);

  // classify a single point
  virtual int                  classify(DataPoint * data_point);

  // classify a single point given a model
  virtual int                  classify(DataPoint *data_point, 
					svm_model *model);

  // get the return values
  virtual  std::vector<double> getValues(svm_node *nodes, 
					 svm_model *model);
}; 

}}

#endif
