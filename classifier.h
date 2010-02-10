#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "feature.h"
#include <vector>
#include "sample.h"
#include <iostream>
#include "featureExtractor.h"

using namespace std;

class Classifier{
 public:
  virtual void train(vector<Feature> * points)=0;
  virtual int  classify(vector<float>  *points)=0;
  void trainOnSet(vector<Sample> * samples);
};


#endif
