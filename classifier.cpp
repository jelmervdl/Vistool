#include "classifier.h"

using namespace std;

vector<int> Classifier::classify(vector<DataPoint> * points){
  vector<DataPoint*> ps = VisionCore::ptrDeMorgan<DataPoint>(points);
  return classify( ps );
}


void Classifier::train(vector<DataPoint> *  files ){
  vector<DataPoint*> ps = VisionCore::ptrDeMorgan<DataPoint>(files);
  return train(ps);
}
