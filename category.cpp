#include "category.h"

int * Category::getEnabled(){
  return &enabled;
}

Category::Category(string give_name, string rt, size_t lab): 
  name(give_name), root(rt), enabled(0), label(lab){
}

vector <DataPoint> * Category::getDataPoints(){
  return &data_points;
}

string Category::getName(){
  return name;
}

void Category::addDataPoint(DataPoint dp){
  data_points.push_back(dp);
}
size_t Category::size(){
  return data_points.size();
}

string Category::getRoot(){
  return root;
}
