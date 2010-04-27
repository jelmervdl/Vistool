#ifndef SEGMENTSVM_H
#define SEGMENTSVM_H

#include "svmclassifier.h"


namespace vito{
namespace classification{

class SegmentSVM : public SVMClassifier{

public:
  SegmentSVM();
  void                         train(std::vector<DataPoint*> data_points);
  std::vector<int>             crossvalidation(std::vector<DataPoint> 
					       *data_points);
  std::vector<int>             classify(std::vector<DataPoint*> data_points);
  int                          classify(DataPoint *data_points);
  Matrix<std::vector <float> > extractKeyPoints(std::vector<float> descriptor);
};

}}

#endif
