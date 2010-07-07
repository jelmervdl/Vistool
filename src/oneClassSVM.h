#ifndef ONECLASSSVM_H
#define ONECLASSSVM_H

#include "svmclassifier.h"

namespace vito{
namespace classification{

class OneClassSVM : public SVMClassifier , public Singleton<OneClassSVM> {
  using SVMClassifier::getSVMParameters;
  int truth_label;

protected:
  virtual double              dataPointLabel(const DataPoint &datapoint);
  svm_parameter              *getSVMParameters();
  virtual std::string         get_name();
  

public:
  virtual void                train(const ExampleCollection &examples);

  void                        set_truth_label(const int i);
                              OneClassSVM();
                              OneClassSVM(int truth_label);
  virtual std::vector<double> getValues(svm_node *nodes, svm_model *model);
  virtual std::vector<double> getValue(const Descriptor &desc,
				       svm_model *model);
  virtual std::vector<double> getValue(const Descriptor &desc);
  //virtual int                 classify(DataPoint *data_point, svm_model *model);
  virtual bool                single_class();
};

}}

#endif
