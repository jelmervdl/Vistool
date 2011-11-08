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
using boost::filesystem::system_complete;

namespace vito{
namespace features{

using write::readDescriptor;
using write::writeDescriptor;

Descriptor FeatureExtractor::getDescriptor(const DataPoint &dp,
					   const bool force,
					   const bool normalize,
					   const bool Stacktraining){

  Descriptor descriptor;
  vector<Feature*> features = getActiveFeatures();

  // if the active feature is a stack feature, recalculate it rather than 
  // loading it from file
  if(features.size() == 1 && features[0]->isStack()){
    //however while optimizing, to save time just keep the non-training points
    //if(Parameters::getInstance()->getiParameter("mode_optimize") > 0){
    //   if(Stacktraining){
    //descriptor = getDescriptorWhileTrainingStack(dp);
    // }
    // else{
    // 	renewDescriptor(dp, force);
    // 	readDescriptor(&descriptor, getCurrentDescriptorLocation(dp));
    //   }

    // }else{ // when not optimizing always recalculate stackfeatures!
    MyImage image(dp, true);
    descriptor = calcDescriptor(image, dp);   
  }else{  
    renewDescriptor(dp, force);
    readDescriptor(&descriptor, getCurrentDescriptorLocation(dp));
  }
  
  return descriptor;
}
   
void FeatureExtractor::saveDescriptorsToFile(Dataset * ds, const bool force)
{
  vector<Category*> enabled= ds->getEnabled();
  for(vector<Category*>::iterator category = enabled.begin();
    category != enabled.end(); ++category)
  {
    string name = (*category)->get_name();
    vector<DataPoint> * files = (*category)->get_data_points();
    string root = (*category)->get_root();
    string aap = DESCRIPTOR_LOCATION;
    path p = complete(path(aap+name));
    path parameters = complete(path(Parameters::getInstance()->getFile()));
    
    // create directory for descriptors
    if (!is_directory(p))
      create_directory(p);
    
    // recalculate descriptors in necessary
    for (vector<DataPoint>::iterator file = files->begin(); file != files->end(); ++file )
      renewDescriptor(*file, force);
  }
}

void FeatureExtractor::assertDir(string str)
{
  path p = complete(path(str));
  
  if(!is_directory(p))
    create_directory(p);
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


vector<float> FeatureExtractor::calcDescriptor(MyImage &image, 
					       const DataPoint &dp){
  vector<Feature*> features = getActiveFeatures();
  vector<float> descriptor;
    for(int i = 0; i < (int) features.size(); ++i){
      features[i]->extractTo(&descriptor, &image);
    }
    return descriptor;
}

Descriptor FeatureExtractor::getDescriptorWhileTrainingStack(const DataPoint &dp){
  string final_descriptor_location = getCurrentDescriptorLocation(dp);
  Descriptor desc;
  if(!exists(path(final_descriptor_location))){
    MyImage image(dp);
    desc = calcDescriptor(image, dp);
  }else{
    readDescriptor(&desc, getCurrentDescriptorLocation(dp));
  }
  return desc;
}

void FeatureExtractor::renewDescriptor(const DataPoint &dp, 
				       const bool force, 
				       const bool train){
  vector<Feature*> features = getActiveFeatures();
  string final_descriptor_location = getCurrentDescriptorLocation(dp);
  if(force || !exists(path(final_descriptor_location))) {
    //cout << "having to rewrite: " << final_descriptor_location << endl;
    MyImage image(dp);
    vector<float> descriptor = calcDescriptor(image, dp);

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
  
  typedef DataPointCollection::const_iterator dpit;
  for(dpit i = dps.begin(); i!= dps.end(); ++i)
    threads.push(new boost::thread( &FeatureExtractor::renewDescriptor, 
				    this, *i, false));
  while(threads.size() != 0 ){
    threads.front()->join();
    delete threads.front();
    threads.pop();
  }
  */

}

bool FeatureExtractor::allExtracted(const DataPointCollection &dps2){
  if(Dataset::prefferredExtracted == true)
    return true;
  Dataset dset = Dataset::getPrefferedDataset();
  const DataPointCollection dps = dset.enabledPoints();
  for(DataPointCollection::const_iterator i = dps.begin(); i!= dps.end(); ++i)
    if(!exists(path(getCurrentDescriptorLocation(*i)))){
      cout << getCurrentDescriptorLocation(*i) << " does exist? " << endl;
      return false;
    }
  Dataset::prefferredExtracted = true;
  return true;
}

DescriptorCollection FeatureExtractor::getExamples(const DataPointCollection &dps){
  // train possible stacks on the examples as well
  vector<Feature*> features = getActiveFeatures();

  for(vector<Feature*>::iterator i = features.begin(); i != features.end(); ++i)
    if((*i)->isStack())
      // don't train when optimizing and all values are saved
	    (*i)->train(dps);
  
  return map(dps, &FeatureExtractor::extractDescriptorWithLabel);
}

DescriptorCollection FeatureExtractor::getDescriptors(const DataPointCollection &dps)
{
  return map(dps, &FeatureExtractor::extractDescriptor);
}

DescriptorCollection FeatureExtractor::map(DataPointCollection const &dps, map_function extractor)
{
  DescriptorCollection descriptors;
  descriptors.reserve(dps.size());

  for(DataPointCollection::const_iterator i = dps.begin(); i != dps.end(); ++i)
  {
    std::cout << "Extracting features: "
      << (i - dps.begin() + 1) << " of " << dps.size()
      << "\r" << std::flush;
    
    descriptors.push_back((this->*extractor)(*i));
  }

  // clean-up line-break.
  std::cout << std::endl;

  assert(dps.size() == descriptors.size());

  return descriptors;
}

Descriptor FeatureExtractor::extractDescriptor(DataPoint const &dp)
{
  return getDescriptor(dp, false, true, true);
}

Descriptor FeatureExtractor::extractDescriptorWithLabel(DataPoint const &dp)
{
  Descriptor descriptor(getDescriptor(dp));
  descriptor.set_label(dp.get_label());
  return descriptor;
}

}}
