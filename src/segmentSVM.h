#ifndef SEGMENTSVM_H
#define SEGMENTSVM_H

#include "svmclassifier.h"
#include <utility>
#include <sstream>
#include <algorithm>

namespace vito{
namespace classification{

class SegmentSVM : public SVMClassifier{
public:
  SegmentSVM();
  std::string             get_name();
  void                    train(std::vector<DataPoint*> data_points);
  std::vector<int>        classify(std::vector<DataPoint*> data_points);
  int                     classify(DataPoint *data_points);
  int                     classify(DataPoint *data_point, svm_model * model);
  Matrix<Descriptor>      extractKeyPoints(const Descriptor &descriptor);
  std::vector<Descriptor> getSubSquares(const Matrix<Descriptor> &keypoints);
  std::vector<Descriptor> getSubregions(const Descriptor &descriptor);
  svm_problem            *compileSegmentProblem(const std::vector<DataPoint*> 
						&data_points);
  void                    fillNodes(svm_node * &nodes, 
				    const Descriptor &descriptor);
};

}}

#endif
