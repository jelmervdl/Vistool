#include "keypoint.h"

using namespace std;
using namespace sift;

size_t KeyPoint::get_center_x(){
  return center_x;
}

size_t KeyPoint::get_center_y(){
  return center_y;
}

float KeyPoint::get_scale(){
  return scale;
}

KeyPoint::KeyPoint(size_t x, size_t y, float s): 
  center_x(x), center_y(y), scale(s) {
}

vector<KeyPoint> sift::divideIntoKeypoints(size_t width, size_t height, 
					   size_t x_points, size_t y_points){
  float x_spacing = width / (float) (x_points);
  float y_spacing = height / (float) (y_points);
  vector<KeyPoint> keypoints;
  for(size_t i = 0; i < x_points; ++i){
    float x = (i + 0.5) * x_spacing;
    for(size_t j = 0; j < y_points; ++j){
      float y = (j + 0.5) * y_spacing;
      KeyPoint new_keypoint((int) (x + 0.5), 
			    (int) (y + 0.5),
			    1.0);
      keypoints.push_back(new_keypoint);
    }
  }
  return keypoints;
}
