#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include"dataPoint.h"

using namespace std;

class Category{
 private:
  string name;
  vector <DataPoint> data_points;
  string root; 
  int enabled; 
 public:
  int * getEnabled();
  Category(string give_name, string root);
  string getRoot();
  size_t size();
  string getName();
  vector <DataPoint> getDataPoints();
  void addDataPoint(DataPoint dp);
};
#endif
