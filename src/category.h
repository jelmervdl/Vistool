#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include"dataPoint.h"

class Category{
 private:
  
  std::string name;
  std::string root; 

  std::vector <DataPoint> data_points;

  int enabled; 
  size_t label;
 public:
  Category(std::string give_name, std::string root, size_t lab);

  size_t size();
  size_t getLabel() const;

  std::string getName();
  std::string getRoot();

  int * getEnabled();
  std::vector <DataPoint> * getDataPoints();

  void addDataPoint(DataPoint dp);
};
#endif
