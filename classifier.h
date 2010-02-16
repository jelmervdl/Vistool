#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include "dataPoint.h"
#include <iostream>
#include "featureExtractor.h"

using namespace std;

class Classifier{
 public:
  virtual void train(vector<DataPoint>     * files )=0;
  virtual int  classify(vector<DataPoint>  * points)=0;
};


#endif
