#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include <Magick++.h>
#include <vector>
#include "parameters.h"
#include "cv.h"
#include "highgui.h"

using namespace cv;
using namespace Magick;

class FeatureExtractor{
 public:
  vector<float> extractHistogram(Mat * mat);
};

#endif
