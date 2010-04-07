#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include <iostream>
#include "classifier.h"
#include "ml.h"
#include "featureExtractor.h"
#include "ocvConvert.h"

using namespace std;

class NNClassifier:public Classifier{
 private:
  CvKNearest * knn;
 public:
  NNClassifier();
  vector<int> crossvalidation(vector<DataPoint> * files);
  void clean();
  void train(vector<DataPoint*> dps);
  int         classify(DataPoint* point);
  vector<int> classify(vector<DataPoint*> point);
  ~NNClassifier();
};

#endif
