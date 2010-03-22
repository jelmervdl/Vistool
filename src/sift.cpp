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
  Matrix<Gradient> gradient = imageGradient(grayscale);

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
      this->drawKeyPoint(draw_me, orientations, *keypoint, new_descriptor, window);
    }
  }
  draw_me.write(visual_representation_location); 
  return (vector<float>) descriptor;
}



void SiftDescriptor::drawKeyPoint(Image &draw_me, const int &orientations,
				  const sift::KeyPoint &keypoint, 
				  const Descriptor &orig_descriptor, 
				  const int &window){
  Parameters *params = Parameters::getInstance();
  const int kHistograms = params->getiParameter("sift_histograms_per_keypoint");
  const int kDescriptors = orig_descriptor.size() / orientations;
  assert(kHistograms * kHistograms == kDescriptors);
  int sub_window_size = (window * 2) / kHistograms;
  draw_me.strokeColor("green");
  draw_me.draw( DrawableCircle(keypoint.get_center_x(),
			       keypoint.get_center_y(),
			       keypoint.get_center_x() + window, 
			       keypoint.get_center_y() ));
  int offset = (sub_window_size / 2) - window;
  for(size_t x = 0; x < (size_t) kHistograms; ++x){
    for(size_t y = 0; y < (size_t) kHistograms; ++y){
      Descriptor descriptor;
      int index = (x + y * kHistograms);
      descriptor.insert(descriptor.end(),
			orig_descriptor.begin() +  index * orientations,
			orig_descriptor.begin() + (index + 1) * orientations);
      int origin_x = keypoint.get_center_x() + offset + sub_window_size * x;
      int origin_y = keypoint.get_center_y() + offset + sub_window_size * y;
      float bin_size = ((2 * PI) / orientations);
      draw_me.strokeColor("red");
      for(int ori = 0; ori < orientations; ++ori){
	float angle = (bin_size * (ori + 1)) - (0.5 * bin_size);
	int end_x = origin_x + descriptor.at(ori) / window * 25 * sin(angle);
	int end_y = origin_y - descriptor.at(ori) / window * 25 * cos(angle);
	draw_me.draw( DrawableLine( origin_x, origin_y, end_x, end_y));
      }
    }
  }
}

Descriptor SiftDescriptor::getKeyPointDescriptor(Matrix<Gradient> * gradient,
						 sift::KeyPoint * keypoint,
						 const size_t window_size,
						 const int kOrientations){
  Parameters * params = Parameters::getInstance();
  int
    window_left  = keypoint->get_center_x() - window_size,
    window_up    = keypoint->get_center_y() - window_size,
    kHistograms = params->getiParameter("sift_histograms_per_keypoint"),
    histogram_range = (2 * window_size) / (kHistograms);
  Descriptor total_bins;
  for(size_t hist_y = 0; hist_y < (size_t) kHistograms; ++hist_y){
    for(size_t hist_x = 0; hist_x < (size_t) kHistograms; ++hist_x){
      int
	left  = window_left + histogram_range * hist_x,
	right = left + histogram_range,
	up = window_up + histogram_range * hist_y,
	down  = up + histogram_range;
      Descriptor bins( kOrientations );
      if(left < 0 || right > (int) gradient->get_width() ||
	 up  < 0 || down > (int) gradient->get_height()){
	cout << "PROBLEMAAAAAA!!!" << endl;
	return bins;
      }
      for(size_t x = left; x < (size_t) right; ++x)
	for(size_t y = up; y < (size_t) down; ++y){
	  gradient::bin(gradient->at(x,y), 
			bins, 1.0);
	}
      total_bins = total_bins + bins;
    }
  }
  return total_bins;
}
