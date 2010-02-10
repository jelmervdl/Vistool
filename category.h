#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>

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
#endif
