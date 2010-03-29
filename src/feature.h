#ifndef FEATURE_H
#define FEATURE_H

#include <vector>
#include "myImage.h"
#include "descriptor.h"


class Feature{
 public:
  Feature();
  virtual Descriptor extract(MyImage * Image, 
				bool makeVisualRepresentation, 
				Image * representation) = 0; 
  vector<float>         extract(MyImage * Image, 
				bool saveVisualRepresentation = false,
				string vis_rep_loc = "rep.jpg" );
  void extractTo(vector<float> * vec, MyImage * im);
};

#endif 
