#include "myImage.h"

namespace vito{

using std::cout;
using std::endl;
using Magick::Image;
using Magick::Blob;
using Magick::ColorGray;
using std::string;
using cv::Mat;


size_t MyImage::get_width(){
  return width;
}

size_t MyImage::get_height(){
  return height;
}

Image* MyImage::getMagickImage(){
  if(magick==NULL){
    magick = new Image(location);
  }
  return magick;
    
}

string MyImage::getLocation(){
  return location;
}


Mat* MyImage::getOpenCVMat(){
  if(mat == NULL)  {
    Mat orig;
    Image * image = getMagickImage();
    magick->magick("BGR");
    Blob blb ;
    magick->write(&blb);
    mat = new Mat();
    orig = Mat(image->size().height(),
	       image->size().width(), 
	       CV_8UC3, 
	       (void *) blb.data());
    cvtColor(orig, *mat, CV_RGB2HSV);
    magick->magick("RGB");
  }
  return mat;

}

Blob *MyImage::getBlob(){
  if(blob==NULL){
    blob = new Blob();
    getMagickImage()->write(blob);
  }
  return blob;
}

MyImage::MyImage(const DataPoint &dp_) : 
  dp(dp_),
  location(dp.get_image_url()),
  magick(0),
  blob(0),
  mat(0){
  width = getMagickImage()->columns();
  height = getMagickImage()->rows();
}

MyImage::MyImage(string loc, DataPoint dp_) : dp(dp_){
  location = loc;
  magick = 0;
  blob = 0;
  mat = 0;
  width = getMagickImage()->columns();
  height = getMagickImage()->rows();
}

MyImage::MyImage(const Image &image) : dp(DataPoint(0, "","","")){
  location = "";
  magick = new Image();
  blob = 0;
  mat = 0;
  *magick = image;
  width = getMagickImage()->columns();
  height = getMagickImage()->rows();
}

Image MyImage::getMagickSubImage(int x, int x_segments, 
				 int y, int y_segments){
  Image magick = *getMagickImage();
  int width = magick.columns();
  int height = magick.rows();
  int left = (x / (float) x_segments) * width;
  int right = ((1 + x) / (float) x_segments) * width;
  int up = (y / (float) y_segments) * height;
  int down = ((1 + y) / (float) y_segments) * height;
  magick.crop(Magick::Geometry(right - left, down - up, left, up));
  return magick;
}

MyImage MyImage::getSubImage(int x, int x_segments, 
		    int y, int y_segments) {
  Image magick = getMagickSubImage(x, x_segments, y, y_segments);
  magick.write("aapie.jpg");
  return MyImage(magick);
}


MyImage::~MyImage(){
  delete mat;
  mat = 0;
  delete magick;
  magick = 0;
  delete blob;
  blob = 0;
}


Matrix<float> MyImage::getGrayscaleMatrix(){
  Image * magick_image = getMagickImage();
  size_t width, height;
  width = magick_image->columns();
  height = magick_image->rows();
  Matrix<float> grayscale (width, height);
  for(size_t x = 0; x < width; ++x){
    for(size_t y = 0; y < height; ++y){
      grayscale.at(x,y) = ((ColorGray) magick_image->pixelColor(x,y)).shade();
      }
  }
  return grayscale;
}

void MyImage::save_sub_image(int x, int x_segments, 
			     int y, int y_segments, 
			     string filename){
  Image magick = getMagickSubImage(x, x_segments, y, y_segments);
  magick.write(filename);
}

}


