#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include "boost/filesystem.hpp"
#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;

class Category{
 private:
  string  name;
  vector <string> files;
 public:
  Category(string give_name);
  size_t size();
  string getName();
  vector <string> file_list();
  void add_file(string  file);
};

class Sample{
 private:
  size_t sample_class;
  string location;
 public:
  Sample(size_t cl, string loc);
  string getLocation();
  size_t getClass();
};

void printDatabase(vector<Category> * db);
bool is_image (string  str);
bool isDataset(string dir, vector<Category> * classes);
void createTrainAndTestSet(vector<Category> * cats, vector<Sample> * samples, vector<string> * targets, float cut);



#endif
