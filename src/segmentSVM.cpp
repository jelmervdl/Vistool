#include "segmentSVM.h"

using std::vector;
using std::cout;
using std::endl;

namespace vito{
namespace classification{

using features::FeatureExtractor;
using write::readDescriptor;

SegmentSVM::SegmentSVM(){
}

Matrix<vector <float> > SegmentSVM::extractKeyPoints(vector<float> descriptor){
  Parameters *p = Parameters::getInstance();
  const int x_keypoints = p->getiParameter("sift_number_of_keypoints_x");
  const int y_keypoints = p->getiParameter("sift_number_of_keypoints_y");
  const int bins = p->getiParameter("sift_orientation_directions");
  Matrix<vector <float> > keypoints (x_keypoints, y_keypoints);
  for(int x = 0; x < x_keypoints; ++x){
    for(int y = 0; y < y_keypoints; ++y){
      keypoints.at(x,y).resize(bins);
      for(int bin = 0; bin < bins; ++bin){
	keypoints.at(x,y)[bin] = descriptor[x * bins + y];
      }
    }
  }
  return keypoints;
}

void SegmentSVM::train(vector<DataPoint*> data_points){
  Parameters *p = Parameters::getInstance();
  p->requireOnlySift();
  svm_parameter *parameters = getSVMParameters();
  vector<float> sample;
  readDescriptor(&sample,
		 FeatureExtractor::getInstance()->
		 getCurrentDescriptorLocation(*data_points[0])); 
  Matrix<vector <float> > keypoints = extractKeyPoints(sample);
}

vector<int> SegmentSVM::crossvalidation(vector<DataPoint> *data_points){
  vector<int> results;
  return results;
}


vector<int> SegmentSVM::classify(vector<DataPoint*> data_points){
  vector<int> results;
  return results;
}

int SegmentSVM::classify(DataPoint *data_point){
  return 0;
}

}}
