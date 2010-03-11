#include "gradient.h"


Gradient::Gradient(float magnitude_, float orientation_)
  :magnitude(magnitude_), orientation(orientation_){
}

Gradient::Gradient(){
};


float Gradient::get_magnitude(){
  return magnitude;
}

float Gradient::get_orientation(){
  return orientation;
}

Gradient singleGradient(Matrix<float> * image, 
		    size_t center_pixel_x, size_t center_pixel_y){
  //Parameters * parameters = Parameters::getInstance();
  size_t width = image->get_width(), height = image->get_height();

  if(center_pixel_x > width - 1 || center_pixel_x < 1 
     || center_pixel_y > height - 1 || center_pixel_y < 1){
    cout << 
      "requesting gradient of out of bound pixel. " <<
      "pixels are out of bounds when they are not within image " << 
      "or within the outermost pixel layer" <<  endl;
    return Gradient(0,0);
  }

  //size_t sift_orientation_directions = parameters->getiParameter("sift_orientation_directions");

  float dx,dy; // dx is the gradient to the right, dy is the gradient to the bottom.
  dx = *image->at(center_pixel_x+1, center_pixel_y) - 
       *image->at(center_pixel_x-1, center_pixel_y);
  dy = *image->at(center_pixel_x, center_pixel_y-1) - 
       *image->at(center_pixel_x, center_pixel_y+1);
  return Gradient (sqrt(dx * dx + dy * dy), atan2( dy, dx));
}

Matrix<Gradient> imageGradient(Matrix<float> * image ){
  size_t width = image->get_width(), height = image->get_height();
  Matrix<Gradient> gradient_image(width-2, height-2);
  for(size_t x = 1; x < image->get_width() - 1; ++x)
    for(size_t y = 1; y < image->get_height() - 1; ++y)
      *gradient_image.at(x - 1, y - 1) = singleGradient(image, x, y);
  return gradient_image;
}
