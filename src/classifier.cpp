#include "classifier.h"

using std::vector;
using std::cout;
using std::endl;

namespace vito{
namespace classification{

Estimation::Estimation(const int i) : result(i), likeliness(1.0), duality(0.0){
  probability[i] = 1.0;
}

Estimation::Estimation(const Probabilities  &probs) : duality(0){
  float max = 0;
  for(Probabilities::const_iterator i = probs.begin(); i != probs.end(); ++i){
    if(i->second > max){
      max = i->second;
      result = i->first;
    }
    duality += i->second;
    probability[i->first] = i->second;
  }
  likeliness = max;
  duality -= likeliness;
}

Estimation Classifier::estimate(const Descriptor &desc){
  return Estimation(classify(desc));
}


EstimationCollection Classifier::estimate(const DescriptorCollection &desc){
  EstimationCollection estimates;
  estimates.reserve(desc.size());
  for(DescriptorCollection::const_iterator i = desc.begin(); i != desc.end(); ++i)
    estimates.push_back(estimate(*i));
  return estimates;
}

LabelCollection Classifier::classify(const DescriptorCollection &descriptors){
  LabelCollection labels;
  labels.resize(descriptors.size());
  for(size_t i = 0; i < descriptors.size(); ++i){
    labels[i] = classify(descriptors[i]);
  }
  return labels;
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
    const int bin_min = (int) ((bin_size * subgroup) + 0.5);
    const int bin_max = (int) ((bin_size * (subgroup + 1) ) + 0.5);
    ExampleCollection training_set;
    ExampleCollection test_set;
    //fill training and test sets:
    for(int i = 0; i < kFiles; ++i)
      if(i >= bin_min && i < bin_max )
	test_set.push_back(files[i]);
      else
	training_set.push_back(files[i]);

    // train on subgroup
    cout << "crossvalidation is training on " << training_set.size() 
	 << " items"  << endl;
    
    train(training_set); 
    DescriptorCollection test_set_descriptor = (DescriptorCollection) test_set;
    // classify test set
    LabelCollection bin_results = classify(test_set_descriptor); 

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
