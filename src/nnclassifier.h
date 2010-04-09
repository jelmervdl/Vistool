#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include <iostream>
#include "classifier.h"
#include "ml.h"
#include "featureExtractor.h"
#include "ocvConvert.h"
#include "tools.h"

namespace VisionToolClassification{

class NNClassifier:public Classifier{
 private:
  CvKNearest * knn;
 public:
  NNClassifier();
  std::vector<int> crossvalidation(std::vector<DataPoint> * files);
  void clean();
  void train(std::vector<DataPoint*> dps);
  int         classify(DataPoint* point);
  std::vector<int> classify(std::vector<DataPoint*> point);
  ~NNClassifier();
};

}

#endif
