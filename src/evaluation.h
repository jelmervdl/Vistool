#ifndef EVALUATION_H
#define EVALUATION_H

#include <sstream>
#include "labels.h"
#include "dataset.h"
#include "classifier.h"

namespace vito{
namespace evaluation{

/* Evaluates classification results given the original datapoints and
 some labels */

struct Stats{
  size_t instances;
  size_t correct;
  size_t handled;
  std::string string();
  float getfmeasure(const float beta);
};

class Evaluation{

public:
  // constructors 
  Evaluation(DataPointCollection &dps,
	     const classification::EstimationCollection &estimations,
	     const float cutoff,
	     const float beta);
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
  float                   getRecall();
  float                   getfmeasure();

  // returns the all points classified as a certain label
  std::vector<DataPoint*> getInstancesClassifiedAs(int cl);

  // classmap getters
  std::map<int, int>      getCorrectMap();
  std::map<int, int>      getTotalMap();
  std::map<int, Stats>    getStatsMap();

private:
  std::map<int, Stats> statsmap;
  size_t correct;
  size_t instances;
  size_t handled;
  size_t ignored;

  float recall;
  float precision;
  float fmeasure;
  bool recallevaluation;


  std::map<int, int> map_correct_to_label;
  std::map<int, int> map_total_to_label;

  std::map<int, std::vector<DataPoint*> > classificationmap;
};

}}

#endif
