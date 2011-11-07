#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "labels.h"
#include "descriptor.h"
#include "parameters.h"
#include <assert.h>

namespace vito{
namespace classification{

typedef std::pair<int, float> Probability;
typedef std::vector<Probability > Probabilities;

struct Estimation{
  Estimation(const int i);
  Estimation(const Probabilities &probs);
  int result;
  std::map<int, float> probability;
  float likeliness;
  float duality;
};

typedef std::vector<Estimation> EstimationCollection;

class Classifier{

public:
  virtual bool             single_class();

  // pure methods
  virtual std::string      get_name() = 0;
  virtual void             train(const DescriptorCollection &examples ) = 0;
  virtual Label            classify(const Descriptor &descriptor ) = 0;
  virtual Estimation       estimate(const Descriptor &descriptor );
  
  // non-virtual generic methods
  LabelCollection      crossvalidation(const DescriptorCollection &files);
  LabelCollection      classify(const DescriptorCollection &descriptors);
  EstimationCollection estimate(const DescriptorCollection &descriptors);

};
  
}}

#endif
