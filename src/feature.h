#ifndef FEATURE_H
#define FEATURE_H

#include <vector>
#include "myImage.h"
#include "descriptor.h"

namespace vito{
namespace features{

class Feature{
 public:
  Feature();
  virtual Descriptor extract_(MyImage *Image, 
			     bool makeVisualRepresentation, 
			     Magick::Image * representation) = 0; 
  std::vector<float> extract(MyImage *Image, 
			     bool saveVisualRepresentation = false,
			     std::string vis_rep_loc = "rep.jpg" );
  void extractTo(std::vector<float> * vec, MyImage * im);
};

}}

#endif 
