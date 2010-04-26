#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include <sstream>
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

  // constructor
                        FeatureExtractor();

  // get active feature classes [BROKEN]
  std::vector<Feature*> usedFeatureKinds();

  //create directory if it doesn't exist
  void                  assertDir(std::string str);

 public:
  // calculate the descriptors to a datapoint, if force is true the
  // descriptor is always calculated
  std::vector<float>    getDescriptor(DataPoint * dp, 
				      const bool force = false);

  // save all active categories within dataset to their respective
  // files.
  void                  saveDescriptorsToFile(Dataset * ds,
					      const bool force = false);

  // renew the a datapoints descriptor if it is required or do it
  // anyway if forced
  void                  renewDescriptor(DataPoint * db,
					const bool force);

  // fill the openCV type matrices given a vector of datapoints
  void                  getCVMatrices(std::vector<DataPoint*> dps,
				      CvMat * training, 
				      CvMat *  labels);
};

}}

#endif
