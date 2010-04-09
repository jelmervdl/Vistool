#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#ifndef DESCRIPTOR_LOCATION
#define DESCRIPTOR_LOCATION "desc/"
#endif

#include <vector>
#include "descriptorWriter.h"
#include "dataset.h"
#include "histogram.h"
#include "sift.h"

namespace VisionToolFeatures{

class FeatureExtractor:public Singleton<FeatureExtractor>{
  friend class Singleton<FeatureExtractor>;
 private:
  std::vector<Feature*> features;
  FeatureExtractor();
 public:
  std::vector< std::vector<float> >  collectDescriptors(std::vector<DataPoint> points);
  std::vector<float>  getDescriptor(DataPoint * dp );
  void saveDescriptorsToFile(Dataset * ds);
  std::vector<std::string> createAndSaveDescriptors(std::vector<Category> * particip);
  void renewDescriptor(DataPoint * db);
  void getCVMatrices(std::vector<DataPoint*> dps, CvMat * training, CvMat *  labels);
};

}

#endif
