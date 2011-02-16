#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#define OMP_NUM_THREADS 1

#include <queue>
#include "boost/thread/thread.hpp"
#include "features.h"
#include <sstream>
#include "descriptorWriter.h"
#include "dataset.h"

namespace vito{
namespace features{

class FeatureExtractor:public Singleton<FeatureExtractor>{
  friend class Singleton<FeatureExtractor>;

 private:
  std::vector<Feature*> features;

  //create directory if it doesn't exist
  void                  assertDir(std::string str);

 public:

  void                  renewDescriptors(const DataPointCollection &dps);
  // calculate the descriptors to a datapoint, if force is true the
  // descriptor is always calculated
  Descriptor            getDescriptor(const DataPoint &dps,
				      const bool force = false);

  // save all active categories within dataset to their respective
  // files.
  void                  saveDescriptorsToFile(Dataset * ds,
					      const bool force = false);

  // refresh the a datapoints descriptor if it is required or do it
  // anyway if forced
  void                  renewDescriptor(const DataPoint &dp,
					const bool force);

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
