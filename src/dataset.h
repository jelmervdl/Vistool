#ifndef DATASET_H
#define DATASET_H

#include <math.h>
#include "core.h"
#include "category.h"
#include <vector>
#include <string>
#include "boost/filesystem.hpp"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "dataPoint.h"
#include "fileManagement.h"
#include <map>

namespace vito{

class Dataset{
 private:
  std::map<size_t, std::string> category_names;
  std::vector<Category> categories;
  std::string root;
 public:
  //constructor:
  Dataset(std::string rt);

  // getters:
  std::vector<Category> * getCategories();
  std::vector<Category*> getEnabled();
  std::string getCatName(size_t cat);
  std::string get_root();
  size_t smallestCategory() ;

  //setters
  void setRoot(std::string str);
  void addCategory(Category cat);

  void enableCategory(size_t i);
  void enableCategory(std::string str);
  void enableRandom(const int number);

  void print();

  std::vector<DataPoint> enabledPoints(bool eqrep = true) ;
  std::vector<DataPoint*> enabledDataPoints(bool eqrep= true);

  void randomDataSplit(std::vector<DataPoint> * train, 
		       std::vector<DataPoint> * test, 
		       float cut = 0.5, 
		       bool eqrep = true);
};
}

#endif
