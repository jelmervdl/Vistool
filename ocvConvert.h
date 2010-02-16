#ifndef OCVCONVERT_H
#define OCVCONVERT_H

#include <vector>
#include "cv.h"
#include <iostream>

using namespace cv;

namespace OCV_Convert{
  Mat_<float> dataset2Mat(vector < vector <float> > * fl);
};

#endif OCVCONVERT_H
