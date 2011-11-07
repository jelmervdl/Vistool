#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include <iostream>
#include "classifier.h"
#include "opencv/ml.h"
#include "featureExtractor.h"
#include "ocvConvert.h"
#include "tools.h"

namespace vito{
namespace classification{
 
class NNClassifier : public Classifier, public Singleton<NNClassifier> {
 private:

  CvKNearest * knn; // the model
 public:
  using Classifier::train;
  using Classifier::classify;

  NNClassifier();
  ~NNClassifier();

  std::string      get_name();
  void             clean();
  void             train(const DescriptorCollection &examples);
  Label              classify(const Descriptor &descriptor );

};

}}

#endif
