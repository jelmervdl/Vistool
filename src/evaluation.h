#ifndef EVALUATION_H
#define EVALUATION_H

#include "labels.h"
#include "dataset.h"

namespace vito{
namespace evaluation{

/* Evaluates classification results given the original datapoints and
 some labels */
class Evaluation{

public:
  // constructors 
  Evaluation();
  Evaluation(DataPointCollection &dps, 
	     const LabelCollection &cls);
  Evaluation(DataPointCollection &dps,
	     const LabelCollection &classification,
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

private:
  size_t correct;
  size_t instances;
  float recall;
  float precision;
  float tval;

  std::map<int, int> map_correct_to_label;
  std::map<int, int> map_total_to_label;

  std::map<int, std::vector<DataPoint*> > classificationmap;
};

}}

#endif
