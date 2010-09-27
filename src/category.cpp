#include "category.h"

namespace vito{

using std::random_shuffle;
using std::string;
using std::vector;

Category::Category(string give_name, string rt, size_t lab): 
  name(give_name), root(rt), enabled(0), label(lab){
}

string Category::get_name() const{
  return name;
}

size_t Category::size() const{
  return data_points.size();
}

string Category::get_root() const{
  return root;
}
size_t Category::get_label() const {
  return label;
}

void Category::addDataPoint(DataPoint dp){
  data_points.push_back(dp);
}

vector<DataPoint> Category::get_data_points_() {
  return data_points;
}

vector <DataPoint> * Category::get_data_points(){
  return &data_points;
}

int * Category::enabledLiveVar(){
  return &enabled;
}

void Category::shuffle(){
  random_shuffle(data_points.begin(),data_points.end());
}

}
