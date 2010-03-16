#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <Magick++.h>
#include <vector>
#include "parameters.h"
#include "cv.h"
#include "highgui.h"
#include "matrix.h"

#include <string>

using namespace std;
using namespace cv;
using namespace Magick;

class MyImage{
 private:
  size_t width, height;
  string location;
  Image * magick;
  Blob * blob;
  Mat * mat;
 public:
  size_t get_width();
  size_t get_height();
  Image  *getMagickImage();
  string getLocation();
  Blob *getBlob();
  Mat * getOpenCVMat();
  Matrix<float> getGrayscaleMatrix();
  MyImage(string loc);
  ~MyImage();
};

#endif
