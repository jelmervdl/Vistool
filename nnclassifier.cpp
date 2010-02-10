#include "nnclassifier.h"

using namespace std;

void NNClassifier::train(vector<Feature> * points){
  size_t k = 10;
  size_t cols, rows;
  rows = points->size();
  cols = points->at(0).getValues().size();
  cout << "rows: " << rows << "cols: " << cols << endl;
  CvMat *traindata = cvCreateMat(cols , rows, CV_32F);
  for(vector<Feature>::iterator it = points->begin(); it != points->end(); ++it){
    cout << "aap" << endl;
    
  }
}
int  NNClassifier::classify(vector<float> * points){
  return 0;
}
