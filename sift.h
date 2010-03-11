#ifndef SIFT_H
#define SIFT_H

#include <math.h>
#include <iostream>
#include "feature.h"
#include "parameters.h"

class SiftDescriptor:public Feature{
 public: 
  vector<float> extract(MyImage * Image,
			bool save_visual_representation = false,
			string visual_representation_location = "rep.jpg");
  void calculateGradient(Matrix<float> image, 
		    size_t pixel_x, size_t pixel_y, 
		    float * magnitude,float * orientation); // these are returned
};

#endif
