#ifndef SIFT_H
#define SIFT_H

#include <math.h>
#include <iostream>
#include "feature.h"
#include "parameters.h"
#include "keypoint.h"
#include "gradient.h"
class SiftDescriptor:public Feature{
 public: 
  vector<float> extract(MyImage * Image,
			bool save_visual_representation = false,
			string visual_representation_location = "rep.jpg");
};



#endif
