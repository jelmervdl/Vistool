#ifndef MYIMAGE_H
#define MYIMAGE_H


#include <Magick++.h>
#include "parameters.h"
#include "cv.h"
#include "dataPoint.h"
#include "highgui.h"
#include "matrix.h"

namespace vito{

namespace features{
class ClassifierSetup;
}

class MyImage{
  friend class features::ClassifierSetup;
 protected:
  DataPoint dp;
  size_t width, height;
  std::string location;
  Magick::Image * magick;
  Magick::Blob * blob;
  cv::Mat * mat;
 public:
  MyImage(const DataPoint &dp);
  MyImage();
  MyImage(std::string loc, DataPoint dp);
  MyImage(const Magick::Image &image);
  ~MyImage();

  size_t          get_width();
  size_t          get_height();
  Magick::Image  *getMagickImage();
  std::string     getLocation();
  Magick::Blob   *getBlob();
  cv::Mat        *getOpenCVMat();
  Matrix<float>   getGrayscaleMatrix();

  // get the Image Magick Image that of the pixel region of zone x/y
  // given a number of segments;
  Magick::Image   getMagickSubImage(int x, int x_segments, 
				   int y, int y_segments) ;

  // get The sub Image and save it
  void            save_sub_image(int x, int x_segments, 
		      int y, int y_segments, 
		      std::string filename);

  // get a sub image and poor it into a MyImage wrapper;
  MyImage         getSubImage(int x, int x_segments, 
			      int y, int y_segments) ;
  //constructors:
};

}

#endif
