#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#define OMP_NUM_THREADS 1

#include "experiment.h"
#include <queue>
#include "boost/thread/thread.hpp"
#include "features.h"
#include <sstream>
#include "descriptorWriter.h"
#include "dataset.h"



namespace vito{
namespace features{

struct NormalizationInfo{
  float min;
  float max;
  bool calibrated;
  void calibrateNormalization(const DataPointCollection &dps);
};

class FeatureExtractor:public Singleton<FeatureExtractor>{
  friend class Singleton<FeatureExtractor>;

 private:
  std::map<std::string, NormalizationInfo> normalizations;

  std::vector<Feature*> features;

  //create directory if it doesn't exist
  void                  assertDir(std::string str);

 public:
  bool                  allExtracted(const DataPointCollection &dps);

  std::vector<float>    calcDescriptor(MyImage &image, const DataPoint &dp);
  void                  renewDescriptors(const DataPointCollection &dps);
  // calculate the descriptors to a datapoint, if force is true the
  // descriptor is always calculated
  Descriptor            getDescriptor(const DataPoint &dps,
				      const bool force = false,
				      const bool normalize = true,
				      const bool stacktraining = false);

  Descriptor            getDescriptorWhileTrainingStack(const DataPoint &dp);

  // save all active categories within dataset to their respective
  // files.
  void                  saveDescriptorsToFile(Dataset * ds,
					      const bool force = false);

  // refresh the a datapoints descriptor if it is required or do it
  // anyway if forced
  void                  renewDescriptor(const DataPoint &dp,
					const bool force,
					const bool train = false);

  std::string           getCurrentDescriptorLocation(const DataPoint &dp);

  // fill the openCV type matrices given a vector of datapoints
  void                  getCVMatrices(std::vector<DataPoint*> dps,
				      CvMat * training, 
				      CvMat *  labels);

  ExampleCollection     getExamples(const DataPointCollection &datapoints);
  DescriptorCollection  getDescriptors(const DataPointCollection &datatpoints);
};

}}

#endif
