#include "myImage.h"

namespace vito{

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

MyImage::MyImage(string loc){
  location = loc;
  magick = 0;
  blob = 0;
  mat = 0;
  width = getMagickImage()->columns();
  height = getMagickImage()->rows();
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
}
