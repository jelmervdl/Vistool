#ifndef FEATURE_H
#define FEATURE_H

#include <vector>
#include "myImage.h"

class Feature{
 public:
  Feature();
  virtual vector<float> extract(MyImage * Image) = 0;
  void extractTo(vector<float> * vec, MyImage * im);
};

#endif 
