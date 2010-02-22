#include "nnclassifier.h"

using namespace cv;
using namespace std;

void NNClassifier::train(vector<DataPoint> dps){
  size_t rows, cols;
  vector<float> sample;
  readDescriptor(&sample, dps[0].getDescriptorURL());
  rows = dps.size();
  cols = sample.size();
  Mat tmatrix(rows, cols, CV_32FC1, Scalar(0.0));
  Mat labels  (rows, 1, CV_32FC1, Scalar(0.0));
  
  for(size_t row = 0; row < rows; ++row){
    vector<float> desc;
    readDescriptor(&desc, dps[row].getDescriptorURL());
    labels.at<int>(row,0) = dps[row].getLabel();
    for(size_t col = 0; col < cols; ++col ){
      tmatrix.at<float>(row,col) = desc[col];

    }
  }
  
  cout << "printing tags" << endl;
  for(size_t i = 0; i < rows; ++i)
    cout << labels.at<int>(i,0);
  cout << endl;

  /*
  //Mat_<float> matrix (10,10,CV_32FC1);
  //Mat_<float> labels (10,10,CV_32FC1);
  //cout << labels.rows << endl;

  
  size_t rows, cols;
  vector<float> sample;
  readDescriptor(&sample, dps[0].getDescriptorURL());
  rows = dps.size();
  cols = sample.size();
  
  CvMat cvm = cvMat(rows,cols,CV_32FC1);
  
  //Mat m = Mat(&cvm,0);

  //  m.at(5,5) = 10;
  //cout << cvmGet(&cvm, 5,5);

  
  CvMatrix traindat (rows, cols, CV_32FC1);
  Mat mat ((const CvMat_<float>*) &traindat);
  Mat_<float> m((const Mat*) & mat);
  CvMat * a = (CvMat*) traindat;
  for(size_t y = 0; y < dps.size(); ++y){
  vector<float> desc;
  readDescriptor(&desc, dps[y].getDescriptorURL());
    for(size_t x = 0; x < desc.size(); ++x ){
      mat(x,y) = desc[x];
    }
  }

  //CvKNearest knn((const CvMat*) &matrix, (const CvMat*) &labs);
  */
}

int  NNClassifier::classify(vector<DataPoint> * datapoints){
  return 0;
}
