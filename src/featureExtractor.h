#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include <vector>
#include "descriptorWriter.h"
#include "dataset.h"
#include "histogram.h"
#include "sift.h"

namespace vito{
namespace features{

class FeatureExtractor:public Singleton<FeatureExtractor>{
  friend class Singleton<FeatureExtractor>;
 private:
  std::vector<Feature*> features;
  std::vector<Feature*> usedFeatureKinds();
  FeatureExtractor();
 public:
  std::vector< std::vector<float> >  collectDescriptors(std::vector<DataPoint> points);

  std::vector<float>  getDescriptor(DataPoint * dp, const bool force = false);
  void saveDescriptorsToFile(Dataset * ds, const bool force = false);

  void renewDescriptor(DataPoint * db, const bool force);
  void getCVMatrices(std::vector<DataPoint*> dps, CvMat * training, CvMat *  labels);
};

}}

#endif
