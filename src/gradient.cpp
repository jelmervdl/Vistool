#include "gradient.h"

using std::cout;
using std::endl;

#define PI 3.14159265

namespace vito {
namespace features {
Gradient::Gradient(float magnitude_, float orientation_)
  :magnitude(magnitude_), orientation(orientation_){
}

Gradient::Gradient(){
};


float Gradient::get_magnitude() const{
  return magnitude;
}

float Gradient::get_orientation() const{
  return orientation;
}

Gradient singleGradient(const Matrix<float>& image, 
			const size_t &center_pixel_x,
			const size_t &center_pixel_y){
  //Parameters * parameters = Parameters::getInstance();
  size_t width = image.get_width(), height = image.get_height();

  if(center_pixel_x > width - 1 || center_pixel_x < 1 
     || center_pixel_y > height - 1 || center_pixel_y < 1){
    cout << 
      "requesting gradient of out of bound pixel. " <<
      "pixels are out of bounds when they are not within image " << 
      "or within the outermost pixel layer" <<  endl;
    return Gradient(0,0);
  }

  float dx,dy; // dx is the gradient to the right, dy is the gradient to the bottom.
  dx = image.at(center_pixel_x+1, center_pixel_y) - 
       image.at(center_pixel_x-1, center_pixel_y);
  dy = image.at(center_pixel_x, center_pixel_y-1) - 
       image.at(center_pixel_x, center_pixel_y+1);
  return Gradient (sqrt(dx * dx + dy * dy), atan2( dx, dy));
}

Matrix<Gradient> imageGradient(const Matrix<float> &image ){
  size_t width = image.get_width(), height = image.get_height();
  Matrix<Gradient> gradient_image(width-2, height-2);
  for(size_t x = 1; x < image.get_width() - 1; ++x)
    for(size_t y = 1; y < image.get_height() - 1; ++y){
      gradient_image.at(x - 1, y - 1) = singleGradient(image, x, y);
    }
  return gradient_image;
}

void bin(Gradient &gradient, Descriptor &bin_values, const float &multiplier){
  float angle = gradient.get_orientation() / PI;
  size_t bins = bin_values.size();
  float bin_size = 2.0 / bins;
  float angle_min = angle - (0.5 * bin_size);
  float angle_max = angle + (0.5 * bin_size);
  
  angle_min = wrap(angle_min);
  angle_max = wrap(angle_max);

  float bin_min;
  float bin_max = 0;
  for(size_t bin = 0; bin < bins; ++bin){
    bin_min = bin_max;
    bin_max = (bin + 1) * bin_size;
    float share;
    if(angle_min >= bin_min && angle_min <= bin_max){
      share = ((bin_max - angle_min) / bin_size);
      bin_values.at(bin) += share * multiplier * gradient.get_magnitude();
    }
    else if(angle_max >= bin_min && angle_max <= bin_max){
      share = ((angle_max - bin_min) / bin_size);
      bin_values.at(bin) += share * multiplier * gradient.get_magnitude();   
    }
  }
}

float wrap(float angle, const float &min, const float &max){
  float period = max - min;
  while(angle < min || angle > max){
    if(angle > max)
      angle -= period;
    else if(angle < min)
      angle += period;
  }
  return angle;
}
}}
