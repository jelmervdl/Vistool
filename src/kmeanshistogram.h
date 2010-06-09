#ifndef KMEANSHISTOGRAM_H
#define KMEANSHISTOGRAM_H

#include "kmeansclustering.h"
#include "feature.h"
#include "patchExtractor.h"

namespace vito{
namespace features{

template <class FeatureType> class KMeansClusterHistogram  : public Feature{
public:

  typedef clustering::patch patch;
  typedef clustering::patch_collection patch_collection;
  typedef clustering::labels labels;
  typedef clustering::label_collection label_collection;

protected:
  patch_collection centers;

public:
  virtual std::string getParameterName(){
    return "";
  }

  virtual bool        isActive(){
    return false;
  }


  KMeansClusterHistogram(std::vector<DataPoint> *dps){
    Feature *feature = FeatureType::getInstance();

    clustering::PatchExtractor patch_extractor;
    clustering::KMeansClustering clustering;

    patch_collection patches = patch_extractor.getPatches(dps, feature);
    centers = clustering.cluster(patches);
  }

  virtual Descriptor  extract_(MyImage *image, 
			      bool makeVisualRepresentation, 
			       Magick::Image * representation){
    Feature *feature = FeatureType::getInstance();
    clustering::KMeansClustering clustering;
    clustering::PatchExtractor patch_extractor;

    patch_collection image_patches = 
      patch_extractor.getPatches(*image, feature);

    labels classification = 
      clustering.classify_per_patch(centers, image_patches);

    const int kClasses = 50;

    vector<float> histogram (kClasses);
    for(size_t i = 0; i < classification.size(); i++)
      histogram[i]++;
    for(size_t i = 0; i < histogram.size(); i++)
      histogram[i] /= (float) classification.size();
    return histogram;

  }
                 
};


}}
#endif
