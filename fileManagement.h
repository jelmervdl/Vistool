#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include "boost/filesystem.hpp"
#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "sample.h"
#include "category.h"

using namespace std;

void printDatabase(vector<Category> * db);
bool is_image (string  str);
bool isDataset(string dir, vector<Category> * classes);
void createTrainAndTestSet(vector<Category> * cats, vector<Sample> * samples, vector<string> * targets, float cut);



#endif
