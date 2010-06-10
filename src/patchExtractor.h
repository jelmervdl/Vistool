#ifndef PATCHEXTRACTOR_H
#define PATCHEXTRACTOR_H

#include "myImage.h"
#include "clustering.h"
#include "datapoint.h"
#include "feature.h"

namespace vito{
namespace clustering{

class PatchExtractor{
public:
  patch_collection getPatches(MyImage &myImage, 
			      features::Feature *feature);
  patch_collection getPatches(DataPoint dp, 
			      features::Feature *feature);
  patch_collection getPatches(std::vector<DataPoint> *dps, 
			      features::Feature *feature);
  patch            getPatch(MyImage *image, 
			    features::Feature *feature);
};


}}

#endif
