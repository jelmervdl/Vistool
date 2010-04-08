#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <Magick++.h>
#include "parameters.h"
#include "cv.h"
#include "highgui.h"
#include "matrix.h"


class MyImage{
 private:
  size_t width, height;
  std::string location;
  Magick::Image * magick;
  Magick::Blob * blob;
  cv::Mat * mat;
 public:
  size_t get_width();
  size_t get_height();
  Magick::Image  *getMagickImage();
  std::string getLocation();
  Magick::Blob *getBlob();
  cv::Mat * getOpenCVMat();
  Matrix<float> getGrayscaleMatrix();
  MyImage(std::string loc);
  ~MyImage();
};

#endif
