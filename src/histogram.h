#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "singleton.h"
#include "feature.h"

namespace vito{
namespace features{

class Histogram : public Feature, public Singleton<Histogram>{
  friend class Singleton<Histogram>;
 public:
  // return activity of feature
  bool       isActive();

  // extract actual descriptor;
  Descriptor extract_(MyImage * Image,  
		     bool saveVisualRepresentation,
		     Magick::Image* image);
};

}}

#endif
