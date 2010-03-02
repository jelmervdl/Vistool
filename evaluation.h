#ifndef EVALUATION_H
#define EVALUATION_H

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include "dataPoint.h"
#include "dataset.h"

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

  static Evaluation kCrossFoldValidation(size_t times, Dataset * ds, bool eqrep = true);
};


#endif
