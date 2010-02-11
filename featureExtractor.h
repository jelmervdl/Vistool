#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#ifndef DESCRIPTOR_LOCATION
#define DESCRIPTOR_LOCATION "desc/"
#endif

#include <Magick++.h>
#include <vector>
#include "parameters.h"
#include "cv.h"
#include "highgui.h"
#include "feature.h"
#include "category.h"
#include "myImage.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include "descriptorWriter.h"

using namespace cv;
using namespace Magick;

class FeatureExtractor{
 public:
  void createAndSaveDescriptors();
  Feature getFeatures(string location);
  vector<float> extractHistogram(MyImage *image);
  void createAndSaveDescriptors(vector<Category> * particip);
};

#endif
