#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <Magick++.h>
#include <vector>
#include "parameters.h"
#include "cv.h"
#include "highgui.h"


#include <string>

using namespace std;
using namespace cv;
using namespace Magick;



class MyImage{
 private:
  string location;
  Image * magick;
  Blob * blob;
  Mat * mat;
 public:
  Image  *getMagickImage();
  string getLocation();
  Mat *getOpenCVMat();
  Blob *getBlob();
  MyImage(string loc);
  ~MyImage();
};

#endif
