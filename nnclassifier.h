#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include <iostream>
#include "classifier.h"
#include "ml.h"
#include "featureExtractor.h"
#include "ocvConvert.h"

using namespace std;

jkdjksadclass NNClassifier:public Classifier{
 private:
  CvKNearest * knn;
  size_t k;
 public:
  NNClassifier(size_t n);
  void clean();
  void train(vector<DataPoint*> dps);
  int         classify(DataPoint* point);
  vector<int> classify(vector<DataPoint*> point);
  ~NNClassifier();
};

#endif
