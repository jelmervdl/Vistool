#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H


#include <vector>
#include "parameters.h"

class FeatureExtractor{
 public:
  vector<float> extractHistogram(Image * image, Blob * blob, Mat * mat);
};

#endif
