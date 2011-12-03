#include "features.h"

#include "mpeg7.h"
#include "facedetect.h"
#include "sift.h"
#include "histogram.h"
#include "classifierStack.h"
#include "rawFeature.h"

using std::vector;
using std::cout;
using std::endl;

namespace vito{
namespace features{

//using mpeg7::EdgeHistogram;
//using mpeg7::ScalableColor;
//using mpeg7::ColorLayout;

vector<Feature*> getExistingFeatures(){
  vector<Feature*> features;
  features.push_back(SiftDescriptor::getInstance());
  features.push_back(Histogram::getInstance());

  //mpeg 7
  features.push_back(EdgeHistogram::getInstance());
  features.push_back(ScalableColor::getInstance());
  features.push_back(ColorLayout::getInstance());
  features.push_back(DominantColor::getInstance());
  features.push_back(ColorStructure::getInstance());
  features.push_back(HomogeneousTexture::getInstance());

  // face detection
  features.push_back(FaceFeature::getInstance());
  ClusterFeatureExtractor *cfe = 
    ClusterFeatureExtractor::getInstance();
  vector<Feature*> clust_feats = cfe->getFeatures();
  for(size_t i = 0; i < clust_feats.size(); i++)
    features.push_back(clust_feats[i]);
  NaiveStackFeatures::getInstance()->add_to(features);
  SVMStackFeatures::getInstance()->add_to(features);

  // raw pixel feature
  features.push_back(RawFeature::getInstance());

  return features;
}

vector<Feature*> getActiveFeatures(){
  vector<Feature*> features = getExistingFeatures();
  vector<Feature*> active_features;
  for(int i = 0; i < (int) features.size(); ++i){
    if(features[i]->isActive())
      active_features.push_back(features[i]);
  }
  return active_features;
}

void printActiveFeatures(){
  vector<Feature*> actives = getActiveFeatures();
  cout << "printing active features:" << endl;
  typedef vector<Feature*>::iterator feat_it;
  for(feat_it i = actives.begin(); i != actives.end(); ++i)
    cout << "active feature n." << i - actives.begin()
	 << "=" << (*i)->getParameterName() << endl;
}
}
}
