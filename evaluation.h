#ifndef EVALUATION_H
#define EVALUATION_H

#include <vector>
#include <map>
#include "dataPoint.h"
#include <iostream>

class Evaluation{
 private:
  size_t correct;
  size_t instances;
  float recall;
  float precision;
  float tval;
  map< int, vector<DataPoint*> > classificationmap;
 public:
  Evaluation(vector<DataPoint> * dps, vector<int> * classification);
  void print();
  size_t getCorrect();
  size_t getInstances();
  float getRecall();
  float getPrecision();
  float getTval();

  vector<DataPoint*> getInstancesClassifiedAs(int cl);
};


#endif
