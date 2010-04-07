#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include "dataPoint.h"
#include <iostream>
#include "featureExtractor.h"
#include "descriptorWriter.h"
#include "core.h"
#include "evaluation.h"

using namespace std;

class Classifier{
 public:
  virtual void train(vector<DataPoint*> files )=0;
  void train(vector<DataPoint> * files );
  virtual vector<int> crossvalidation(vector<DataPoint> * files) = 0 ;
  virtual vector<int> classify(vector<DataPoint*>  points)=0;
  vector<int> classify(vector<DataPoint> * points);
  virtual int classify(DataPoint * point) = 0;
};


#endif
