#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include "dataPoint.h"
#include <iostream>
#include "featureExtractor.h"

using namespace std;

class Classifier{
 public:
  virtual void train(vector<string> * files)=0;
  virtual int  classify(vector<float>  *points)=0;
  void trainOnSet(vector<DataPoint> * data_points);
};


#endif
