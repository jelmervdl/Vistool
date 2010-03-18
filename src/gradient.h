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

using namespace std;
namespace gradient{

class Gradient{
 private:
  float magnitude;
  float orientation;
  friend std::ostream& operator<<(std::ostream& os, const Gradient& p){
    return os << p.magnitude;
  }
 public:
  float get_magnitude();
  float get_orientation();
  Gradient();
  Gradient(float magnitude_, float orientation_);

};

Gradient singleGradient(Matrix<float> * image, 
			size_t center_pixel_x, size_t center_pixel_y); 
 Matrix<Gradient> imageGradient(Matrix<float> * image);
 void bin(Gradient * gradient, Descriptor * bins, float multiplier);
 float wrap(float angle, float min = 0.0, float max = 2.0);
}
#endif

