#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "singleton.h"
#include "feature.h"

namespace VisionToolFeatures{

class Histogram: public Singleton<Histogram>, public Feature{
  friend class Singleton<Histogram>;
 public:
  Histogram();
  Descriptor extract(MyImage * Image,  
		     bool saveVisualRepresentation,
		     Magick::Image* image);
};

}

#endif
