#include "classifier.h"

using std::vector;
using std::cout;
using std::endl;

namespace vito{
namespace classification{

LabelCollection Classifier::classify(DescriptorCollection descriptors){
  LabelCollection labels(descriptors.size());
  transform(descriptors.begin(), descriptors.end(), 
	    labels.begin(), mem_fun(*Classifier::classify));

}


LabelCollection Classifier::crossvalidation(const ExampleCollection &files){
  // ready CrossValidation Parameters
  const int kFolds = 
    Parameters::getInstance()->getiParameter("cross_validation_k");
  const int kFiles = files.size();
  assert(kFolds > 1);
  // fill in results of training/classification on k subgroups
  LabelCollection results(kFiles);
  const float bin_size = kFiles / (float) kFolds;
  for(int subgroup = 0; subgroup < kFolds; ++subgroup){
    ExampleCollection training_set;
    ExampleCollection test_set;
    const int bin_min = (int) ((bin_size * subgroup) + 0.5);
    const int bin_max = (int) ((bin_size * (subgroup + 1) ) + 0.5);
    //fill training and test sets:
    for(int i = 0; i < kFiles; ++i)
      if(i >= bin_min && i < bin_max )
	test_set.push_back(files[i]);
      else
	training_set.push_back(files[i]);
    train(training_set); // train on subgroup
    LabelCollection bin_results = classify(test_set); // classify test set
    // fill in results of last classification
    for(int i = bin_min; i < bin_max; ++i)
      results[i] = bin_results[i - bin_min];
  }
  return results;
}

bool Classifier::single_class(){
  return false;
}

}}
