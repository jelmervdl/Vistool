#ifndef KMEANSHISTOGRAM_H
#define KMEANSHISTOGRAM_H

#include <sstream>
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
  patch_collection         centers;
  std::string feature_type;


public:
  virtual std::string getParameterName(){
    return feature_type;
  }

  virtual bool isActive(){
    std::stringstream ss;
    ss << "feature_" <<  feature_type;
    std::cout << "is this feature active?:" << ss.str() << " answer: " 
	      << Parameters::getInstance()->getiParameter(ss.str()) << std::endl;
    return Parameters::getInstance()->getiParameter(ss.str());
  }


  KMeansClusterHistogram(std::vector<DataPoint> *dps){
    Feature *feature = FeatureType::getInstance();
    std::stringstream ss;
    ss << "kmeans_clustered_feature_using_visual_patches_"
       << feature->getParameterName() << "_of_" 
       << dps->size() << "_images";
    feature_type = ss.str();
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

    std::cout  << "just made a class of size: " << classification.size() << std::endl;
    std::cout << " with content: " << std::endl;
    for(size_t i = 0; i < classification.size(); i++)
      std::cout << classification[i]  << " ";
    std::cout << std::endl;

    const int kClasses = 50;    
    std::vector<float> histogram (kClasses);
    std::cout << "the hist content: " << std::endl;
    for(size_t i = 0; i < classification.size(); i++)
      histogram[classification[i]]++;
    for(size_t i = 0; i < histogram.size(); i++){
      //histogram[i] /= (float) classification.size();
      std::cout << i << ":" << histogram[i] << ", ";
    }
    std::cout << std::endl;
    return histogram;
  }                 
};


}}
#endif
