#include "myImage.h"

using namespace std;
using namespace Magick;
using namespace cv;

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
    orig = Mat(image->size().height(),
	       image->size().width(), 
	       CV_8UC3, 
	       (void *) blb.data());
    mat = new Mat();
    cvtColor(orig, *mat, CV_BGR2HSV);
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
}

MyImage::~MyImage(){
  delete mat;
  mat = 0;
  delete magick;
  magick = 0;
  delete blob;
  blob = 0;
}
