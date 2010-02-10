#include "category.h"

Category::Category(string give_name){
    name = give_name;
}

vector <string> Category::file_list(){
  return files;
}

string Category::getName(){
  return name;
}

void Category::add_file(string file){
  files.push_back(file);
}
size_t Category::size(){
  return files.size();
}

