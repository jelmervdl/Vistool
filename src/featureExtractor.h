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

using namespace cv;
using namespace Magick;

class FeatureExtractor:public Singleton<FeatureExtractor>{
  friend class Singleton<FeatureExtractor>;
 private:
  vector<Feature*> features;
  FeatureExtractor();
 public:
  vector< vector<float> >  collectDescriptors(vector<DataPoint> points);
  vector<float>  getDescriptor(DataPoint * dp );
  void saveDescriptorsToFile(Dataset * ds);
  vector<string> createAndSaveDescriptors(vector<Category> * particip);
  void renewDescriptor(DataPoint * db);
  void getCVMatrices(vector<DataPoint*> dps, CvMat * training, CvMat *  labels);
};

#endif
