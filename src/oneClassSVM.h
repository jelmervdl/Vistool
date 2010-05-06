#ifndef ONECLASSSVM_H
#define ONECLASSSVM_H

#include "svmclassifier.h"

namespace vito{
namespace classification{

class OneClassSVM : public SVMClassifier {
  using SVMClassifier::getSVMParameters;
  const int truth_label;
protected:
  virtual double      dataPointLabel(const DataPoint &datapoint);
  svm_parameter      *getSVMParameters();
  virtual std::string get_name();

public:
                      OneClassSVM(int truth_label);
  virtual std::vector<double> getValues(svm_node *nodes, svm_model *model);

};

}}

#endif
