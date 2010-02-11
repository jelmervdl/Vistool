#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include <iostream>
#include "classifier.h"
#include "ml.h"

using namespace std;

class NNClassifier:public Classifier{
 public:
  void train(vector<string> * files)=0;
  int classify(vector<float>  *points);
};

#endif
