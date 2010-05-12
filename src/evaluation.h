#ifndef EVALUATION_H
#define EVALUATION_H

#include "dataset.h"

namespace vito{
namespace evaluation{

class Evaluation{

private:
  size_t correct;
  size_t instances;
  float recall;
  float precision;
  float tval;

  std::map<int, int> map_correct_to_label;
  std::map<int, int> map_total_to_label;

  std::map<int, std::vector<DataPoint*> > classificationmap;

public:
  // constructors 
                          Evaluation(std::vector<DataPoint*> &dps,
				     std::vector<int> &cls);
                          Evaluation(std::vector<DataPoint> * dps,
				     std::vector<int> * classification);
                          Evaluation(std::vector<DataPoint> * dps,
				     std::vector<int> * classification,
				     int one_class_t);

  // print a summary of this evaluation
  void                    print();

  // getting certain statistical properties
  size_t                  getCorrect();
  size_t                  getInstances();
  float                   getPrecision();
  
  // returns the all points classified as a certain label
  std::vector<DataPoint*> getInstancesClassifiedAs(int cl);

  // classmap getters
  std::map<int, int>      getCorrectMap();
  std::map<int, int>      getTotalMap();
};

}}

#endif
