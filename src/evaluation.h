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
  std::map<int, int> map_correct_to_label;
  std::map<int, int> map_total_to_label;
  std::map< int, std::vector<DataPoint*> > classificationmap;
public:
  Evaluation(std::vector<DataPoint*> &dps, std::vector<int> &cls);
  Evaluation(std::vector<DataPoint> * dps, std::vector<int> * classification);
  void print();
  size_t getCorrect();
  size_t getInstances();
  float getRecall();
  float getPrecision();
  float getTval();
  
  std::vector<DataPoint*> getInstancesClassifiedAs(int cl);
  std::map<int, int> getCorrectMap();
  std::map<int, int> getTotalMap();
};


#endif
