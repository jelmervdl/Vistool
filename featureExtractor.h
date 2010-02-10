#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include <Magick++.h>
#include <vector>
#include "parameters.h"
#include "cv.h"
#include "highgui.h"
#include "feature.h"

using namespace cv;
using namespace Magick;

class FeatureExtractor{
 public:
  Feature getFeatures(string location);
  vector<float> extractHistogram(Mat * mat);
};

#endif
