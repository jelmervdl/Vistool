#ifndef FEATURE_H
#define FEATURE_H

#include "myImage.h"
#include "descriptor.h"

namespace vito{
namespace features{


/* Feature Extractor class */
class Feature{
  float min;
  float max;
  bool norm;
public:

  //constructor
                             Feature();
                            ~Feature();

  // features name;
  virtual std::string        getParameterName() = 0;

  //returns whether the feature is currently active or not
  virtual bool               isActive();

  virtual bool               isStack();

  virtual void train (DataPointCollection dps){return;};

  //actually extracts the descriptor
  virtual Descriptor         extract_(MyImage *Image, 
				      bool makeVisualRepresentation, 
				      Magick::Image * representation) = 0; 

  // saves any possible representations
  virtual std::vector<float> extract(MyImage *Image, 
				     bool saveVisualRepresentation = false,
				     std::string vis_rep_loc = "rep.jpg" );

  // extracts feature to a vector
  virtual void               extractTo(std::vector<float> * vec,
				       MyImage * im);
};

}}

#endif 
