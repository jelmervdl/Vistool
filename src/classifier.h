#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "labels.h"
#include "descriptor.h"
#include "featureExtractor.h"

namespace vito{
namespace classification{

class Classifier{

public:
  virtual bool             single_class();
  // pure methods
  virtual std::string      get_name() = 0;
  virtual void             train(const ExampleCollection &examples ) = 0;
  virtual Label            classify(const Descriptor &descriptor ) = 0;

  // generic methods
  LabelCollection  crossvalidation(const ExampleCollection &files);
  LabelCollection  classify(const DescriptorCollection &descriptor);


};
  
}}

#endif
