#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include "boost/filesystem.hpp"
#include <list>
#include <stdio.h>
#include <iostream>

using namespace std;

class Category{
 private:
  string  name;
  list <string> files;
 public:
  Category(string give_name);
  size_t size();
  string getName();
  list <string> file_list();
  void add_file(string  file);
};

void printDatabase(list<Category> * db);
bool is_image (string  str);
bool isDataset(string dir, list<Category> * classes);


#endif
