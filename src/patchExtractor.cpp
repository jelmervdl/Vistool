#include "patchExtractor.h"

using std::vector;

namespace vito { 
namespace clustering{

using features::Feature;

patch_collection PatchExtractor::getPatches(DataPoint dp, Feature *feature){
  vector<DataPoint> dps(1, DataPoint(dp));
  return getPatches(&dps, feature);
}

patch_collection PatchExtractor::getPatches(vector<DataPoint> *dps, 
					    Feature *feature){
  patch_collection ret;
  const int x_bins = 10;
  const int y_bins = x_bins;
  for(vector<DataPoint>::iterator it = dps->begin();
      it != dps->end();
      ++it){
    MyImage current_image(it->get_image_url());
    for(int x = 0; x < x_bins; x++)
      for(int y = 0; y < y_bins; y++){
	MyImage subImage = current_image.getSubImage(x, x_bins, y, y_bins);
	patch current_patch = getPatch(&subImage, feature);
	ret.push_back(current_patch);
      }
  }
  return ret;
}

patch PatchExtractor::getPatch(MyImage *image, Feature *feature){
  return feature->extract(image);
}


}}
