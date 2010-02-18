#include "nnclassifier.h"

using namespace std;

void NNClassifier::train(vector<DataPoint> dps){
  vector<vector <float> > featureMatrix;
  vector<vector <int> > labels;
  for(vector<DataPoint>::iterator dp = dps.begin(); dp != dps.end(); ++dp){
    vector<float> a;
    readDescriptor(&a, dp->getDescriptorURL());
    featureMatrix.push_back(a);
    vector<int> labels;
    labels.push_back(dp->getLabel());
  }
  Mat_<float> matrix = OCV_Convert::dataset2Mat<float>(&featureMatrix);
}

int  NNClassifier::classify(vector<DataPoint> * datapoints){
  return 0;
}
