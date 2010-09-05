#ifndef GRADIENT_H
#define GRADIENT_H

#include <ostream>
#include <iostream>
#include <iostream>
#include <math.h>

#include "feature.h"
#include "parameters.h"
#include "descriptor.h"

namespace vito{
namespace features{

class Gradient{
 private:
  float magnitude;
  float orientation;
  friend std::ostream& operator<<(std::ostream& os, 
				  const Gradient& p){
    return os << p.magnitude;
  }

 public:
  //getter and setters
  float get_magnitude() const;
  float get_orientation() const;

  //constructors 
        Gradient();
        Gradient(float magnitude_, float orientation_);

};

// gradient features:
// create a gradient for a single pixel in an image
Gradient         singleGradient(const Matrix<float> &image, 
				const size_t &center_pixel_x,
				const size_t &center_pixel_y); 

// create a gradient for an entire image
Matrix<Gradient> imageGradient(const Matrix<float>  &image);

// bin gradients together to make a histogram
void             bin(Gradient &gradient, 
		     Descriptor  &bins, 
		     const float &multiplier);

// wrap a radian (default an angle devided by pi is assumed (0-2))
// angle
float            wrap(float angle, 
		      const float &min = 0.0, 
		      const float &max = 2.0);
}
}
#endif

