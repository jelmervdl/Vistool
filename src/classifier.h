#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "featureExtractor.h"

namespace vito{
namespace classification{

class Classifier{
public:
  virtual bool             single_class();
  virtual std::string      get_name() = 0;
  virtual void             train(std::vector<DataPoint*> files ) = 0;
  virtual void             train(std::vector<DataPoint> * files );

  virtual std::vector<int> crossvalidation(std::vector<DataPoint> * files) = 0 ;

  virtual std::vector<int> classify(std::vector<DataPoint*>  points) = 0;
  virtual std::vector<int> classify(std::vector<DataPoint> * points);
  virtual int              classify(DataPoint * point) = 0;
};
  
}}

#endif
