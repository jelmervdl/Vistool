#include "feature.h"

Feature::Feature(){
  cout << "making feature" << endl;
}

void Feature::extractTo(vector<float> * vec, MyImage * im){
  vector<float> extr = extract(im);
  vec->insert(vec->end(), extr.begin(), extr.end()); 
}

