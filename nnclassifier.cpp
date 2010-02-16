#include "nnclassifier.h"

using namespace std;

void NNClassifier::train(vector<DataPoint> * dps){
  FeatureExtractor f;
  vector< vector<float> > descriptors;
  vector< vector<int>   > labels;
  for(vector<DataPoint>::iterator dp = dps->begin(); dp != dps->end(); ++dp){
    descriptors.push_back(f.getDescriptor(*dp));
    vector<int> n;
    n.push_back(dp->getLabel());
    labels.push_back(n);
  }
}

int  NNClassifier::classify(vector<DataPoint> * datapoints){
  return 0;
}
