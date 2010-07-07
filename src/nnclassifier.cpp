#include "nnclassifier.h"

#define PrepareMatrices(examples)					\

using std::string;
using Magick::Image;
using cv::Mat;

namespace vito{
namespace classification{

using features::FeatureExtractor;
using write::readDescriptor;

string NNClassifier::get_name(){
  return "NNClassifier";
}
NNClassifier::NNClassifier() : knn(0){
  cout << "creating nn classifier" << endl;
}

NNClassifier::~NNClassifier(){
  delete knn;
  cout << "deleting nn classifier" << endl;
}

void NNClassifier::clean(){
  delete knn;
  knn = 0;
}

void NNClassifier::train(const ExampleCollection &examples){
  size_t rows, cols;							
  rows = examples.size();						
  cols = examples[0].size();						
  CvMat * tmat = cvCreateMat(rows, cols, CV_32FC1);			
  CvMat * labs = cvCreateMat(rows, 1, CV_32FC1);			
  Mat labels(labs, 0);							
  Mat tmatrix(tmat, 0);							
  for(size_t row = 0; row < examples.size(); ++row){
    labels.at<int>(row,0) = examples[row].get_label();			
    for(size_t col = 0; col < examples[0].size(); ++col ){
      tmatrix.at<float>(row,col) = examples[row][col];
    }
  }
  clean();
  knn = new CvKNearest(tmat, labs);  
}

Label  NNClassifier::classify(const Descriptor &descriptor){
  DescriptorCollection desc_col(1);
  desc_col[0] = descriptor;
  const int k = Parameters::getInstance()->getiParameter("knn_classifier_k");
  LabelCollection results;
  size_t rows, cols;							
  rows = 1;
  cols = descriptor.size();						
  CvMat * tmat = cvCreateMat(rows, cols, CV_32FC1);			
  Mat tmatrix(tmat, 0);							
  for(size_t col = 0; col < cols; ++col )
    tmatrix.at<float>(0,col) = descriptor[col];
  CvMat *results_mat = cvCreateMat(desc_col.size(),1,CV_32FC1);
  // actual classification
  knn->find_nearest(tmat, k, results_mat);
  Mat  res(results, 0);
  return res.at<int>(0,0);
}

}}
