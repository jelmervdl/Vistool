#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include <iostream>
#include "classifier.h"
#include "ml.h"
#include "feature.h"

using namespace std;

class NNClassifier:public Classifier{
 public:
  void train(vector<Feature> * points);
  int classify(vector<float>  *points);
};

#endif
