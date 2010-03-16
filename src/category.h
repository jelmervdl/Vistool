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
  size_t label;
 public:
  int * getEnabled();
  Category(string give_name, string root, size_t lab);
  string getRoot();
  size_t size();
  string getName();
  size_t getLabel();
  vector <DataPoint> * getDataPoints();
  void addDataPoint(DataPoint dp);
};
#endif
