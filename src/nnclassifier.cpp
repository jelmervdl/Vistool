#include "nnclassifier.h"
#include "tools.h"

#define PrepareMatrices(dps)						\
  size_t rows, cols;							\
  vector<float> sample;							\
  readDescriptor(&sample, dps.at(0)->getDescriptorURL());		\
  rows = dps.size();							\
  cols = sample.size();							\
  CvMat * tmat = cvCreateMat(rows, cols, CV_32FC1);			\
  CvMat * labs = cvCreateMat(rows, 1, CV_32FC1);			\
  FeatureExtractor::getInstance()->getCVMatrices(dps, tmat, labs);	

using namespace cv;
using namespace std;

vector<int> NNClassifier::crossvalidation(vector<DataPoint> * files){
  return Classifier::crossvalidation(files);
}

NNClassifier::NNClassifier() : knn(0){
}

NNClassifier::~NNClassifier(){
  delete knn;
}

void NNClassifier::clean(){
  if(knn != 0){
    delete knn;
    knn = 0;
  }
}

void NNClassifier::train(vector<DataPoint*> dps){
  cout << "training" << endl;
  PrepareMatrices(dps);
  cout << knn << endl;
  clean();
  knn = new CvKNearest(tmat, labs);  
}

vector<int>  NNClassifier::classify(vector<DataPoint*> datapoints){
  vector<int> classes;
  PrepareMatrices(datapoints);
  CvMat * results = cvCreateMat(datapoints.size(),1,CV_32FC1);
  const int k = Parameters::getInstance()->getiParameter("knn_classifier_k");
  knn->find_nearest(tmat, k, results);
  Mat  res(results, 0);
  classes.resize(results->rows);
  for(size_t i = 0; i < (size_t) results->rows; ++i){
    classes.at(i) = res.at<int>(i,0);
  }
  return classes;
}

int  NNClassifier::classify(DataPoint * datapoint){
  if(knn == NULL){
    cout << "trying to classify without training at all" << endl;
    return 0;
  }
  vector<DataPoint*> dv;
  dv.push_back(datapoint);
  return classify(dv)[0];
}
