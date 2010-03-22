#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "singleton.h"
#include "feature.h"

class Histogram: public Singleton<Histogram>, public Feature{
  friend class Singleton<Histogram>;
 public:
  Histogram();
  vector<float> extract(MyImage * Image,  
			bool saveVisualRepresentation,
			Image* image);
};

#endif
