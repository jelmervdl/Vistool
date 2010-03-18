#include "sift.h"
#define PI 3.14159265

using namespace std;
using namespace gradient;

vector<float> SiftDescriptor::extract(MyImage * my_image,
		      bool save_visual_representation ,
		      string visual_representation_location ){
  //Arrange structures
  Descriptor descriptor;
  Parameters * parameters = Parameters::getInstance();
  Matrix<float> grayscale = my_image->getGrayscaleMatrix();
  Matrix<Gradient> gradient = imageGradient(&grayscale);

  //get Parameters
  const int orientations = parameters->getiParameter("sift_orientation_directions");
  const int kKeyPoints_x = parameters->getiParameter("sift_number_of_keypoints_x");
  const int kKeyPoints_y = parameters->getiParameter("sift_number_of_keypoints_x");
  int window_dummy;
  if(parameters->getiParameter("sift_keypoint_pixel_window") < 0)
    window_dummy = min((gradient.get_width() -3) / (2 * kKeyPoints_x),
			   (gradient.get_height() -3)  / (2 * kKeyPoints_y));
  else 
    window_dummy = parameters->getiParameter("sift_keypoint_pixel_window");
  const int window = window_dummy;

  //Spread up Keypoints
  vector<sift::KeyPoint> keypoints = sift::divideIntoKeypoints(gradient.get_width(), 
							       gradient.get_height(), 
							       kKeyPoints_x, kKeyPoints_y);
  Image draw_me;
  if(save_visual_representation){
    draw_me = *my_image->getMagickImage();
    draw_me.fillColor(Color());
  }
  //gather descriptors
  for(vector<sift::KeyPoint>::iterator keypoint = keypoints.begin();
      keypoint != keypoints.end(); ++keypoint){ 
    Descriptor new_descriptor = getKeyPointDescriptor( &gradient, &(*keypoint),  window, 
						      orientations);
    descriptor = descriptor + new_descriptor;
    if(save_visual_representation){
      this->drawKeyPoint(&draw_me, orientations, &*keypoint, &new_descriptor, window);
    }
  }
  draw_me.write(visual_representation_location); 
  return (vector<float>) descriptor;
}



void SiftDescriptor::drawKeyPoint(Image * draw_me, const int orientations,
				   sift::KeyPoint * keypoint, Descriptor * descriptor, const int window){
  draw_me->strokeColor("green");
  draw_me->draw( DrawableCircle(keypoint->get_center_x(), 
			       keypoint->get_center_y(),
			       keypoint->get_center_x() + window, 
			       keypoint->get_center_y() ));
  float bin_size = ((2 * PI) / orientations);
  draw_me->strokeColor("red");
  for(int ori = 0; ori < orientations; ++ori){
    float angle = (bin_size * (ori + 1)) - (0.5 * bin_size);
    draw_me->draw( DrawableLine(keypoint->get_center_x(), keypoint->get_center_y(),
			       keypoint->get_center_x() + descriptor->at(ori) / window * 5 * sin(angle),
			       keypoint->get_center_y() - descriptor->at(ori) / window * 5 * cos(angle)));
  }
}
  


Descriptor SiftDescriptor::getKeyPointDescriptor(Matrix<Gradient> * gradient,
						    sift::KeyPoint * keypoint,
						    const size_t window_size,
						    const int kOrientations){
  int 
    left  = keypoint->get_center_x() - window_size, 
    right = keypoint->get_center_x() + window_size, 
    up    = keypoint->get_center_y() - window_size,
    down  = keypoint->get_center_y() + window_size;
  Descriptor bins( kOrientations );
  if(left < 0 || right > (int) gradient->get_width() ||
     up  < 0 || down > (int) gradient->get_height()){
    return bins;
  }
  for(size_t x = left; x < (size_t) right; ++x){
    for(size_t y = up; y < (size_t) down; ++y){
      gradient::bin(gradient->at(x,y),&bins, 1.0);
    }
  }
  return bins;
}
