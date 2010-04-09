#ifndef GRADIENT_H
#define GRADIENT_H

#include <math.h>
#include <iostream>
#include "feature.h"
#include "parameters.h"
#include <ostream>
#include <iostream>
#include <string>
#include "descriptor.h"

namespace VisionToolFeatures{

class Gradient{
 private:
  float magnitude;
  float orientation;
  friend std::ostream& operator<<(std::ostream& os, const Gradient& p){
    return os << p.magnitude;
  }
 public:
  float get_magnitude() const;
  float get_orientation() const;
  Gradient();
  Gradient(float magnitude_, float orientation_);

};

  Gradient singleGradient(const VisionToolCore::Matrix<float> &image, 
			 const size_t &center_pixel_x,
			 const size_t &center_pixel_y); 
  VisionToolCore::Matrix<Gradient> imageGradient(const VisionToolCore::Matrix<float>  &image);
  void bin(Gradient &gradient, Descriptor  &bins, const float &multiplier);
  float wrap(float angle, const float &min = 0.0, const float &max = 2.0);
}
#endif

