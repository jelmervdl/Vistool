#include "category.h"

Category::Category(string give_name, string rt){
    name = give_name;
    root = rt;
}

vector <DataPoint> Category::getDataPoints(){
  return data_points;
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
