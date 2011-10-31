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
  return &magick;
    
}

string MyImage::getLocation(){
  return location;
}


Mat* MyImage::getOpenCVMat(){
  if(mat == NULL)  {
    try {
      Mat orig;
      getMagickImage();
      magick.magick("BGR");
      Blob blb ;
      magick.write(&blb);
      mat = new Mat();
      orig = Mat(magick.size().height(),
  	       magick.size().width(), 
  	       CV_8UC3, 
  	       (void *) blb.data());
      cvtColor(orig, *mat, CV_RGB2HSV);
      magick.magick("RGB");
    }
    catch (Magick::Exception &e)
    {
      cout << "Caught a magick exception: " << e.what() << endl;
      throw e;
    }
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

MyImage::MyImage(const DataPoint &dp_, bool dummy) : 
  serial(Parameters::getInstance()->getserial()),
  dp(dp_),
  location(dp.get_image_url()),
  magick(0),
  blob(0),
  mat(0){
}

MyImage::MyImage(const DataPoint &dp_) : serial(Parameters::getInstance()->getserial()),
					 dp(dp_),
					 location(dp.get_image_url()),
					 blob(0),
					 mat(0){
  magick = Image(location);
  width = getMagickImage()->columns();
  height = getMagickImage()->rows();
}

MyImage::MyImage(string loc, DataPoint dp_) : serial(Parameters::getInstance()->getserial()),
					      dp(dp_){
  location = loc;
  blob = 0;
  mat = 0;
  std::cout << "making image at: " << location << std::endl;
  magick = Image(location);
  width = getMagickImage()->columns();
  height = getMagickImage()->rows();
}

MyImage::MyImage(const Image &image) : serial(Parameters::getInstance()->getserial()),
				       dp(DataPoint(0, "","","")){
  location = "";
  magick = image;
  blob = 0;
  mat = 0;
  width = getMagickImage()->columns();
  height = getMagickImage()->rows();
}

Image MyImage::getMagickSubImage(int x, int x_segments, 
				 int y, int y_segments) {
  Image new_mag = *getMagickImage();
  int width = new_mag.columns();
  int height = new_mag.rows();
  int left = (x / (float) x_segments) * width;
  int right = ((1 + x) / (float) x_segments) * width;
  int up = (y / (float) y_segments) * height;
  int down = ((1 + y) / (float) y_segments) * height;
  new_mag.crop(Magick::Geometry(right - left, down - up, left, up));
  return new_mag;
}


MyImage::~MyImage(){
  if(mat != 0){
    delete mat;
    mat = 0;
  }
  /*
  if(magick != 0){
    magick.write("honky.jpg");
    cout << "written image " << magick->columns() << " " << magick->rows() << endl;
    delete magick;
    magick = 0;
    }*/
  if(blob != 0){
    delete blob;
    blob = 0;
  }
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
  Image magick_ = getMagickSubImage(x, x_segments, y, y_segments);
  magick_.write(filename);
}

DataPoint MyImage::getDataPoint(){
  return dp;
}

}


