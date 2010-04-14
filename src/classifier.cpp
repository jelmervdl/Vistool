#include "classifier.h"

using VisionToolFeatures::Descriptor;
using std::vector;

namespace VisionToolClassification{

vector<int> Classifier::classify(vector<DataPoint> * points){
  vector<DataPoint*> ps = VisionCore::ptrDeMorgan<DataPoint>(points);
  return classify( ps );
}


void Classifier::train(vector<DataPoint> *  files ){
  vector<DataPoint*> ps = VisionCore::ptrDeMorgan<DataPoint>(files);
  return train(ps);
}


vector<int> Classifier::crossvalidation(vector<DataPoint> * _files)
{
  vector<DataPoint> &files = *_files;
  const int kFolds = Parameters::getInstance()->getiParameter("cross_validation_k");
  const int kFiles = files.size();
 
  assert(kFolds > 1);

  vector<int> results(kFiles);
  const float bin_size = kFiles / (float) kFolds;

  for(int subgroup = 0; subgroup < kFolds; ++subgroup){
    vector<DataPoint*> training_set;
    vector<DataPoint*> test_set;

    const int bin_min = (int) ((bin_size * subgroup) + 0.5);
    const int bin_max = (int) ((bin_size * (subgroup + 1) ) + 0.5);

    //fill training and test sets:
    for(int i = 0; i < kFiles; ++i)
      if(i >= bin_min && i < bin_max )
	test_set.push_back(&files[i]);
      else
	training_set.push_back(&files[i]);
    train(training_set);
    vector<int> bin_results = classify(test_set);
    for(int i = bin_min; i < bin_max; ++i)
      results[i] = bin_results[i - bin_min];

  }
  return results;
}

}
