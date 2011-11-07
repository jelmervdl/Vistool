#ifndef SVMCLASSIFIER_H
#define SVMCLASSIFIER_H

#include "dataPoint.h"
//#include "featureExtractor.h"
#include "classifier.h"
#include "svm.h"

namespace vito{
namespace classification{

void svm_destroy_problem(svm_problem *problem);

class SVMClassifier : public Classifier {
 protected:
  svm_model *model;
  svm_problem *prblm;

  void                         addExampleToProblem(svm_problem &problem, const Descriptor &example);
  virtual std::string          get_name();
  virtual double               dataPointLabel(const DataPoint &datapoint);
  virtual svm_problem         *compileProblem(const DescriptorCollection &files);
  virtual svm_parameter       *getSVMParameters();
  svm_node                    *constructNode(const Descriptor &descriptor);
  svm_parameter               *new_svm_parameters();
 
 public:
  using Classifier::train;
  using Classifier::classify;

  SVMClassifier() : model(0), prblm(0){};
  ~SVMClassifier();
  // train the svm
  virtual void                 train(const DescriptorCollection &files);
  virtual Label                classify(const Descriptor &descriptor);
  virtual int                  classify(const Descriptor &data_point, 
					svm_model *model);
  virtual Estimation           estimate(const Descriptor &descriptor);

  // get the return values
  virtual  std::vector<double> getValues(svm_node *nodes, 
					 svm_model *model);
  virtual std::vector<double>  getValues(const Descriptor &descriptor);
  std::vector<double>          getValuesPerClass(svm_node *nodes,
						 svm_model *model);
  //get current model's class labels
  std::vector<int>                  getLabels();
};
class SVMClassifier_ : public SVMClassifier, public Singleton<SVMClassifier>{};

}
}

#endif
