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


vector<float> SiftDescriptor::getSiftDescriptor(MyImage * my_image){
  Parameters * parameters = Parameters::getInstance();
  Matrix<float> grayscale = my_image->getGrayscaleMatrix();
  size_t width = grayscale.get_width();
  size_t height = grayscale.get_height();
  // generate keypoint grid
  vector<sift::KeyPoint> keypoints = 
    sift::divideIntoKeypoints(width, height, 
			parameters->getiParameter("sift_number_of_keypoints_x"),
			parameters->getiParameter("sift_number_of_keypoints_y"));
  // generate gradient
  Matrix<Gradient> gradient = imageGradient(&grayscale);
  int window = parameters->getiParameter("sift_keypoint_pixel_window");
  if(window < 0)
    window = min(width / parameters->getiParameter("sift_keypoint_pixel_window_x"),
		     height / parameters->getiParameter("sift_keypoint_pixel_window_y"));
  // create descriptor
  vector<Descriptor> descriptor;
  for(vector<sift::KeyPoint>::iterator keypoint = keypoints.begin();
      keypoint != keypoints.end(); ++keypoint){ 
    descriptor += getKeyPointDescriptor(&gradient, &(*keypoint), (const size_t) window, 
					(const int) parameters->getiParameter("sift_orientation_directions"));
  }
}

vector<Descriptor> SiftDescriptor::getKeyPointDescriptor(Matrix<Gradient> * gradient,
						    sift::KeyPoint * keypoint,
						    const size_t window_size,
						    const int kOrientations){
  int 
    left  = keypoint->get_center_x() - window_size, 
    right = keypoint->get_center_x() + window_size, 
    up    = keypoint->get_center_y() - window_size,
    down  = keypoint->get_center_y() + window_size;
  vector<Descriptor> bins( kOrientations );

  if(left < 0 || right > (int) gradient->get_width() ||
     up  < 0 || down > (int) gradient->get_height()){
    cout << "PROBLEM! keypoint out of bounds!" << endl;
    return bins;
  }
  printf( "window: %d left: %d right %d\n", window_size, left, right);
  for(size_t x = left; x < (size_t) right; ++x){
    for(size_t y = up; y < (size_t) down; ++y){
      gradient::bin(gradient->at(x,y),&bins, 1.0);
    }
  }

  return bins;
}
