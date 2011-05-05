#include "featureExtractor.h"

using std::stringstream;
using std::string;
using std::vector;
using std::queue;
using std::cout;
using std::endl;
using cv::Mat;

using boost::filesystem::path;
using boost::filesystem::native;
using boost::filesystem::complete;

namespace vito{
namespace features{

using write::readDescriptor;
using write::writeDescriptor;

  Descriptor FeatureExtractor::getDescriptor(const DataPoint &dp,
						const bool force){
  renewDescriptor(dp, force);
  Descriptor descriptor;
  readDescriptor(&descriptor, getCurrentDescriptorLocation(dp));
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
      cout << "creating directory " << name << endl;
      create_directory(p);
    }
    for(vector<DataPoint>::iterator file = files->begin(); file != files->end(); ++file ){
      renewDescriptor(*file, force);
    }
  }
}

void FeatureExtractor::assertDir(string str){
  path p = complete(path(str, native));
  if(!is_directory(p)){
    cout << "creating directory " << str << endl;
    create_directory(p);
  }
}

string FeatureExtractor::getCurrentDescriptorLocation(const DataPoint &dp){
  Parameters *pars = Parameters::getInstance();
  string general_descriptor_dir = "desc/";
  stringstream 
    hash_descriptor_dir, 
    category_descriptor_dir, 
    final_descriptor_location;
  stringstream xml_file;
  xml_file 
   << "settings/" << pars->getCurrentHash() << ".xml";
  hash_descriptor_dir 
    << general_descriptor_dir 
    << pars->getCurrentHash() << "/";
  assertDir(hash_descriptor_dir.str());
  category_descriptor_dir 
    << hash_descriptor_dir.str() 
    << dp.get_cat_name() << "/";
  assertDir(category_descriptor_dir.str());
  final_descriptor_location 
    << category_descriptor_dir.str() 
    << dp.get_file_name() << ".desc";
  if(!exists( path(xml_file.str())))
    pars->saveXML(xml_file.str());
  return final_descriptor_location.str();
}



void FeatureExtractor::renewDescriptor(const DataPoint &dp, const bool force){
  string final_descriptor_location = getCurrentDescriptorLocation(dp);
  if(force || !exists(path(final_descriptor_location))) {
    Magick::Image imer(dp.get_image_url());
    MyImage image(dp.get_image_url(), dp);
    vector<float> descriptor;
    vector<Feature*> features = getActiveFeatures();
    //printActiveFeatures();
    for(int i = 0; i < (int) features.size(); ++i){
      features[i]->extractTo(&descriptor, &image);
    }
    writeDescriptor(&descriptor,final_descriptor_location);
  } 
}

void FeatureExtractor::getCVMatrices(vector <DataPoint*>  dps, CvMat * training,
				     CvMat *  labs){
  Mat labels(labs, 0);
  Mat tmatrix(training, 0);
  for(size_t row = 0; row < dps.size(); ++row){
    vector<float> desc;
    readDescriptor(&desc, getCurrentDescriptorLocation(*dps.at(row)));
    labels.at<int>(row,0) = dps.at(row)->get_label();
    for(size_t col = 0; col < desc.size(); ++col ){
      tmatrix.at<float>(row,col) = desc[col];
    }
  }
}

void FeatureExtractor::renewDescriptors(const DataPointCollection &dps){
  const int kThreads = 1;
  queue<boost::thread*> threads;
  typedef DataPointCollection::const_iterator dp_it;
  for(dp_it i = dps.begin(); i!= dps.end(); ++i){
    renewDescriptor(*i, false); 
  }
  /*
  DataPointCollection::const_iterator it = dps.begin();
  while(it != dps.end() && (it - dps.begin()) < kThreads){
    threads.push(new boost::thread( &FeatureExtractor::renewDescriptor, this, *it, false));
    it++;
  }
  while(it != dps.end()){
    threads.front()->join();
    delete threads.front();
    threads.pop();
    threads.push(new boost::thread( &FeatureExtractor::renewDescriptor, this, *it, false));
    it++;
  }
  while(threads.size() > 0){
    threads.front()->join();
    delete threads.front();
    threads.pop();
  }
  */
}

ExampleCollection FeatureExtractor::getExamples(const DataPointCollection &dps){
  {
    vector<Feature*> features = getActiveFeatures();
    typedef vector<Feature*>::iterator fe_it;
    for(fe_it i = features.begin(); i != features.end(); ++i)
      (*i)->train(dps);
  }
  renewDescriptors(dps);
  ExampleCollection examples(dps.size());
  for(size_t i = 0; i < dps.size(); ++i){
    Example current_example(getDescriptor(dps[i]));
    current_example.set_label(dps[i].get_label());
    examples[i] = current_example;
  }
  return examples;
}

DescriptorCollection FeatureExtractor::getDescriptors(const DataPointCollection &dps){
  renewDescriptors(dps);
  DescriptorCollection descriptors(dps.size());
  for(size_t i = 0; i < dps.size(); ++i){
    Descriptor current_descriptor(getDescriptor(dps[i]));
    descriptors[i] = current_descriptor;
  }
  return descriptors;
}

}}
