#ifndef DATASET_H
#define DATASET_H

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

using namespace std;

class Dataset{
 private:
  map<size_t, string> category_names;
  vector<Category> categories;
  string root;
 public:
  //constructor:
  Dataset(string rt);

  // getters:
  vector<Category> * getCategories();
  vector<Category*> getEnabled();
  string getCatName(size_t cat);
  string getRoot();
  size_t smallestCategory() ;


  void setRoot(string str);
  void addCategory(Category cat);

  void enableCategory(size_t i);
  void enableCategory(string str);


  void print();
  void printEnabled();

  vector<DataPoint> enabledPoints(bool eqrep = true) ;
  vector<DataPoint*> enabledDataPoints(bool eqrep= true);

  void randomDataSplit(vector<DataPoint> * train, 
		       vector<DataPoint> * test, 
		       float cut = 0.5, 
		       bool eqrep = true);
};



#endif
