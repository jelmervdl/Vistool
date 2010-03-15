#include "sift.h"

using namespace std;
using namespace gradient;
// Sift

vector<float> SiftDescriptor::extract(MyImage * my_image,
		      bool save_visual_representation ,
		      string visual_representation_location ){

  vector<float> descriptor;
  return descriptor;
}



vector<float> getKeyPointDescriptor(MyImage * my_image,
				    sift::KeyPoint * keypoint){
  size_t window_size = 10;
  int 
    left  = keypoint->get_center_x() - window_size, 
    right = keypoint->get_center_x() + window_size, 
    up    = keypoint->get_center_y() - window_size,
    down  = keypoint->get_center_y() + window_size;
  vector<float> bins(10);
  Matrix<float> grayscale = my_image->getGrayscaleMatrix();
  Matrix<Gradient> gradient = imageGradient(&grayscale);

  if(left < 0 || right > (int) gradient.get_width() ||
     up  < 0 || down > (int) gradient.get_height()){
    cout << "PROBLEM! keypoint out of bounds!" << endl;
    return bins;
  }
  for(size_t x = left; x < (size_t) right; ++x){
    for(size_t y = up; y < (size_t) down; ++y){
      gradient::bin(gradient.at(x,y),&bins, 1.0);
    }
  }

  return bins;
}
