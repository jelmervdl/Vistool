#include "sample.h"


Sample::Sample(size_t cl, string loc){
  sample_class = cl;
  location = loc;
}

string Sample::getLocation(){
  return location;
}

size_t Sample::getClass(){
  return sample_class;
}
