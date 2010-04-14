#ifndef SIFT_H
#define SIFT_H

#include <math.h>
#include <iostream>
#include "feature.h"
#include "parameters.h"
#include "keypoint.h"
#include "gradient.h"
#include "descriptor.h"

namespace vito{
namespace features{

class SiftDescriptor: public Feature, public Singleton<SiftDescriptor>{
  friend class Singleton<SiftDescriptor>;
 public: 
  Descriptor extract(MyImage *Image,
		     bool save_visual_representation,
		     Magick::Image *canvas);
  Descriptor getKeyPointDescriptor(Matrix<Gradient> * gradient,
				   sift::KeyPoint * keypoint,
				   const size_t window_size,
				   const int kOrientations);
  void drawKeyPoint(Magick::Image &draw_me, const int &orientations,
		    const sift::KeyPoint &keypoint, 
		    const Descriptor &descriptor, const int &window);

};

}}

#endif
