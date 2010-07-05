#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "featureExtractor.h"

namespace vito{
namespace classification{

/* Algorithm that can provide a classification of a datapoints given
   after learning from a given set of datapoints and labels.
 */
class Classifier{
public:
  virtual bool             single_class();

  /* return the classifier's name to be used in lists and the
     generation of hashable string */
  virtual std::string      get_name() = 0;
  virtual std::vector<int> crossvalidation(std::vector<DataPoint> * files);
  virtual std::vector<int> classify(std::vector<DataPoint*>  points) = 0;
  virtual int              classify(DataPoint * point) = 0;
  virtual void             train(std::vector<DataPoint*> files ) = 0;

  void                     train(std::vector<DataPoint> * files );
  std::vector<int>         classify(std::vector<DataPoint> * points);

};
  
}}

#endif
