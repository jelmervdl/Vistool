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

void NormalizationInfo::calibrateNormalization(const DataPointCollection &dps){
  cout << "calibrating normalization... " << endl;
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  typedef DataPointCollection::const_iterator dpcit;
  for(dpcit i = dps.begin(); i != dps.end(); ++i){
    float cmin, cmax;
    Descriptor current_descriptor = fe->getDescriptor(*i, false, false, true);
    cout << Parameters::getInstance()->getCurrentHash() << " " << current_descriptor.size() << endl;
    cmin = *std::min_element(current_descriptor.begin(),
			     current_descriptor.end());
    cmax = *std::max_element(current_descriptor.begin(), 
			     current_descriptor.end());
    if(cmin < min || i == dps.begin())
      min = cmin;
    if(cmax > max || i == dps.begin())
      max = cmax;
  }
  cout << "calibration results: min = " << min << " max = " << max << endl;
  calibrated = true;
}

Descriptor FeatureExtractor::getDescriptor(const DataPoint &dp,
					   const bool force,
					   const bool normalize,
					   const bool Stacktraining){

  // if we are to normalize, assure normalization has been calibrated
  NormalizationInfo *info = 0;
  if(normalize){
    stringstream hash;
    hash << Parameters::getInstance()->getCurrentHash();
    info = &normalizations[hash.str().c_str()];
    if(!info->calibrated)
      info->calibrateNormalization(Dataset::getPrefferedDataset().enabledPoints());
  }
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
  if(normalize){
    descriptor.normalize(info->min, info->max);
  }
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
    path p = complete(path(aap+name));
    path parameters = complete(path(Parameters::getInstance()->getFile()));
    if(!is_directory(p)){
      cout << "creating directory " << p.string() << endl;
      create_directory(p);
    }
    for(vector<DataPoint>::iterator file = files->begin(); file != files->end(); ++file ){
      renewDescriptor(*file, force);
    }
  }
}

void FeatureExtractor::assertDir(string str){
  path p = complete(path(str));
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
    cout << "having to rewrite: " << final_descriptor_location << endl;
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

ExampleCollection FeatureExtractor::getExamples(const DataPointCollection &dps){
  // train possible stacks on the examples as well
  vector<Feature*> features = getActiveFeatures();

  for(vector<Feature*>::iterator i = features.begin(); i != features.end(); ++i)
    if((*i)->isStack())
      // don't train when optimizing and all values are saved
	(*i)->train(dps);

  // Add Labels to Descriptors and return
  ExampleCollection examples;
  examples.reserve(dps.size());
  for(DataPointCollection::const_iterator i = dps.begin(); i != dps.end(); ++i){
    Example current_example(getDescriptor(*i, 0, true, true));
    current_example.set_label(i->get_label());
    examples.push_back(current_example);
  }
  return examples;
}

DescriptorCollection FeatureExtractor::getDescriptors(const DataPointCollection
						      &dps){
  DescriptorCollection descriptors;
  descriptors.reserve(dps.size());
  for(DataPointCollection::const_iterator i = dps.begin(); i != dps.end(); ++i)
    descriptors.push_back(getDescriptor(*i));
  return descriptors;
}

}}
