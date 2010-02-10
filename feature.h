#ifndef FEATURE_H
#define FEATURE_H

#include<vector>

using namespace std;

class Feature{
 private:
  vector<float> features;
 public:
  vector<float> getValues();
  Feature(vector<float> inits);
};


#endif
