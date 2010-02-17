#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include <iostream>
#include "classifier.h"
#include "ml.h"
#include "featureExtractor.h"
#include "ocvConvert.h"

using namespace std;

class NNClassifier:public Classifier{
 public:
  void train(vector<DataPoint> files);
  int classify(vector<DataPoint>  *points);
};

#endif
