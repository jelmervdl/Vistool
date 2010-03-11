#include "sift.h"

using namespace std;

vector<float> SiftDescriptor::extract(MyImage * my_image,
		      bool save_visual_representation ,
		      string visual_representation_location ){

  vector<float> descriptor;
  return descriptor;
}

void SiftDescriptor::calculateGradient(Matrix<float> image, 
			     size_t center_pixel_x, size_t center_pixel_y, 
			     float * magnitude, float * orientation){
  Parameters * parameters = Parameters::getInstance();
  size_t width = image.get_width(), height = image.get_height();

  if(center_pixel_x > width - 1 || center_pixel_x < 1 
     || center_pixel_y > height - 1 || center_pixel_y < 1){
    cout << 
      "requesting gradient of out of bound pixel. " <<
      "pixels are out of bounds when they are not within image " << 
      "or within the outermost pixel layer" <<  endl;
    return;
  }

  //size_t sift_orientation_directions = parameters->getiParameter("sift_orientation_directions");

  float dx,dy; // dx is the gradient to the right, dy is the gradient to the bottom.
  dx = *image.at(center_pixel_x+1, center_pixel_y) - 
       *image.at(center_pixel_x-1, center_pixel_y);
  dy = *image.at(center_pixel_x, center_pixel_y-1) - 
       *image.at(center_pixel_x, center_pixel_y+1);

  *magnitude =  sqrt(dx * dx + dy * dy);
  *orientation = atan2( dy, dx);
}



