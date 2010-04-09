#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include "dataPoint.h"
#include <iostream>
#include "featureExtractor.h"
#include "descriptorWriter.h"
#include "core.h"
#include "evaluation.h"

namespace VisionToolClassification{

class Classifier{
 public:
  virtual void train(std::vector<DataPoint*> files )=0;
  void train(std::vector<DataPoint> * files );
  virtual std::vector<int> crossvalidation(std::vector<DataPoint> * files) = 0 ;
  virtual std::vector<int> classify(std::vector<DataPoint*>  points)=0;
  std::vector<int> classify(std::vector<DataPoint> * points);
  virtual int classify(DataPoint * point) = 0;
};

}

#endif
