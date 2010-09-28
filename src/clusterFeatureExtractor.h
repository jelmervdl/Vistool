#ifndef CLUSTERFEATUREXTRACTOR_H
#define CLUSTERFEATUREXTRACTOR_H

#include "kmeanshistogram.h"

namespace vito{
namespace features{

class ClusterFeatureExtractor : public Singleton<ClusterFeatureExtractor> {

public:
  typedef std::vector<DataPoint> datapoint_list;
  typedef std::vector<Feature*> feature_list;

protected:
  feature_list currentFeatures;
  int current;

public:
  ~ClusterFeatureExtractor(){
    clear();
  }

  void clear(){
    while(currentFeatures.size() > 0){
      delete currentFeatures.back();
      currentFeatures.pop_back();
    }
  }

  void addClusterFeature(KMeansClusterHistogram *histogram){
    currentFeatures.push_back(histogram);
  }

  std::string addClusterFeature(const datapoint_list &dps, Feature *feature){
    Feature *new_feature = new KMeansClusterHistogram(dps, feature);
    currentFeatures.push_back(new_feature);
    return new_feature->getParameterName();
  }

  feature_list getFeatures(){
    return currentFeatures;
  }

};

}}
#endif
