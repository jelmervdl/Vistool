#include "feature.h"

vector<float> Feature::getValues(){
  return features;
}

Feature::Feature(vector<float> inits){
  features = inits;
}
