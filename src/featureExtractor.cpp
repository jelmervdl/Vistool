#include "featureExtractor.h"

using std::string;
using std::vector;
using cv::Mat;

using boost::filesystem::path;
using boost::filesystem::native;
using boost::filesystem::complete;

namespace vito{
namespace features{

using write::readDescriptor;
using write::writeDescriptor;

vector<Feature*> FeatureExtractor::usedFeatureKinds(){
  vector<Feature*> feats;
  Parameters *parameters = Parameters::getInstance();
  if(parameters->getiParameter("feature_histogram") > 0){
    Histogram *hist = Histogram::getInstance();
    feats.push_back(hist);
  }
  if(parameters->getiParameter("feature_sift") > 0){
    feats.push_back((SiftDescriptor* ) SiftDescriptor::getInstance());
  }
  return feats;
}

FeatureExtractor::FeatureExtractor(){
  Parameters *parameters = Parameters::getInstance();
  if(parameters->getiParameter("feature_histogram") > 0){
    Histogram *hist = Histogram::getInstance();
    features.push_back(hist);
  }
  if(parameters->getiParameter("feature_sift") > 0){
    features.push_back((SiftDescriptor* ) SiftDescriptor::getInstance());
  }
}

  vector<float> FeatureExtractor::getDescriptor(DataPoint * dp, const bool force){
  renewDescriptor(dp, force);
  vector<float>  descriptor;
  readDescriptor(&descriptor, dp->get_descriptor_url());
  return descriptor;
}
   
  void FeatureExtractor::saveDescriptorsToFile(Dataset * ds, const bool force){
  vector<Category*> enabled= ds->getEnabled();
  for(vector<Category*>::iterator category = enabled.begin();
      category != enabled.end();
      ++category){
    string name = (*category)->get_name();
    vector<DataPoint> * files = (*category)->get_data_points();
    string root = (*category)->get_root();
    string aap = DESCRIPTOR_LOCATION;
    path p = complete(path(aap+name, native));
    path parameters = complete(path(Parameters::getInstance()->getFile()));
    if(!is_directory(p)){
      printf("creating directory %s\n", name.c_str());
      create_directory(p);
    }
    for(vector<DataPoint>::iterator file = files->begin(); file != files->end(); ++file ){
      renewDescriptor(&*file, force);
    }
  }
}

  void FeatureExtractor::renewDescriptor(DataPoint * dp, const bool force){
  path parameters = complete(path(Parameters::getInstance()->getFile()));
  Parameters *pars = Parameters::getInstance();
  if(force
     ||
     !exists(path(dp->get_descriptor_url())) 
     ||
     last_write_time(parameters) < last_write_time(path(dp->get_image_url()))){
    MyImage image(dp->get_image_url());
    vector<float> descriptor;
      //vector<float> temp_desc = (*it)->extract_(&image, false, NULL);
      //descriptor.insert(descriptor.end(), temp_desc.begin(), temp_desc.end());
    if(pars->getiParameter("feature_histogram") > 0){
      Histogram *hist = Histogram::getInstance();
      vector<float> desc = hist->extract_(&image, false, (Magick::Image*) NULL);
      descriptor.insert(descriptor.end(), desc.begin(), desc.end());
    }
    if(pars->getiParameter("feature_sift") > 0){
      SiftDescriptor *sift = SiftDescriptor::getInstance();
      vector<float> desc = sift->extract_(&image, false, (Magick::Image*) NULL);
      descriptor.insert(descriptor.end(), desc.begin(), desc.end());
    }
    writeDescriptor(&descriptor,dp->get_descriptor_url());
    printf("renewing descriptor for %s\n", dp->get_image_url().c_str());
  } 
}

void FeatureExtractor::getCVMatrices(vector <DataPoint*>  dps, CvMat * training,
				     CvMat *  labs){
  Mat labels(labs, 0);
  Mat tmatrix(training, 0);
  for(size_t row = 0; row < dps.size(); ++row){
    vector<float> desc;
    readDescriptor(&desc, dps.at(row)->get_descriptor_url());
    labels.at<int>(row,0) = dps.at(row)->get_label();
    for(size_t col = 0; col < desc.size(); ++col ){
      tmatrix.at<float>(row,col) = desc[col];
    }
  }
}

}}
