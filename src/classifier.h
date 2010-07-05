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
  virtual int              classify() = 0;

  // generic methods
  virtual LabelCollection  crossvalidation(const ExampleCollection &files);
  virtual LabelCollection  classify(DescriptorCollection descriptor);


};
  
}}

#endif
