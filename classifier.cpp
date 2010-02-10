#include "classifier.h"

using namespace std;

void Classifier::trainOnSet(vector<Sample> * samples){
  cout << "classifying " << samples->size() << "samples" << endl;
  FeatureExtractor *f = new FeatureExtractor();
  vector<Feature> features;
  for(vector<Sample>::iterator it = samples->begin(); it != samples->end(); ++it){
    cout << it->getLocation() << endl;
    //features.push_back(f->getFeatures(it->getLocation()));
    //samples->getLocation();
  }
  delete f;
}
