#include "featureExtractor.h"

using namespace Magick;
using namespace std;
using namespace cv;
using namespace boost::filesystem;

FeatureExtractor::FeatureExtractor(){
  Histogram * hist = (Histogram *) Histogram::getInstance();
  features.push_back(hist);
}

vector<float> FeatureExtractor::getDescriptor(DataPoint * dp ){
  renewDescriptor(dp);
  vector<float>  descriptor;
  readDescriptor(&descriptor, dp->getDescriptorURL());
  return descriptor;
}
   
void FeatureExtractor::saveDescriptorsToFile(Dataset * ds){
  vector<Category*> enabled= ds->getEnabled();
  for(vector<Category*>::iterator category = enabled.begin();
      category != enabled.end();
      ++category){
    string name = (*category)->getName();
    vector<DataPoint> * files = (*category)->getDataPoints();
    string root = (*category)->getRoot();
    string aap = DESCRIPTOR_LOCATION;
    path p = complete(path(aap+name, native));
    path parameters = complete(path(Parameters::getInstance()->getFile()));
    if(!is_directory(p))
      create_directory(p);
    for(vector<DataPoint>::iterator file = files->begin(); file != files->end(); ++file ){
      renewDescriptor(&*file);
    }
  }
}

void FeatureExtractor::renewDescriptor(DataPoint * dp){
  path parameters = complete(path(Parameters::getInstance()->getFile()));
  if(!exists(path(dp->getDescriptorURL())) 
     ||
     last_write_time(parameters) < last_write_time(path(dp->getImageURL()))){
    MyImage image(dp->getImageURL());
    vector<float> descriptor;
    for(vector<Feature*>::iterator feature = features.begin(); feature != features.end(); ++feature){
      (*feature)->extractTo(&descriptor, &image);
    }
    ((Histogram*)Histogram::getInstance())->extractTo(&descriptor, &image);
    writeDescriptor(&descriptor,dp->getDescriptorURL());
  } 
}

void FeatureExtractor::getCVMatrices(vector <DataPoint*>  dps, CvMat * training,
				     CvMat *  labs){
  Mat labels(labs, 0);
  Mat tmatrix(training, 0);
  for(size_t row = 0; row < dps.size(); ++row){
    vector<float> desc;
    readDescriptor(&desc, dps.at(row)->getDescriptorURL());
    labels.at<int>(row,0) = dps.at(row)->getLabel();
    for(size_t col = 0; col < desc.size(); ++col ){
      tmatrix.at<float>(row,col) = desc[col];
    }
  }
}

