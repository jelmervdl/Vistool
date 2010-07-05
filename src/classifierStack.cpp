#include "classifierStack.h"

using std::stringstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ostream_iterator;
using Magick::Image;

namespace vito{

using classification::Classifier;
using features::Feature;

namespace features {

ClassifierSetup::ClassifierSetup(Classifier *c, string xmlfile) : classifier(c){
  string old_name = Parameters::get_current_name();
  parameters = Parameters::getUnique();
  Parameters::setUnique(parameters);
  Parameters::getInstance()->readFile(xmlfile.c_str());
  Parameters::select(old_name);
}

ClassifierSetup::ClassifierSetup( Classifier *c) : classifier(c){
  Parameters *old = Parameters::getInstance();
  string old_name = Parameters::get_current_name();
  parameters = Parameters::getUnique();
  Parameters::setUnique(parameters);
  *Parameters::getInstance() = *old;
  Parameters::select(old_name);
}

void ClassifierSetup::train(vector<DataPoint*> dps){
  string previous_parameters = Parameters::get_current_name();
  Parameters::setUnique(parameters);
  cout << "current hashable string is: " 
       << Parameters::getInstance()->getHashableString() << endl;
  cout << "the current hash is: " 
       << Parameters::getInstance()->getCurrentHash() << endl;
  for(size_t i = 0; i < dps.size(); i++)
    FeatureExtractor::getInstance()->renewDescriptor(dps[i], false);
  classifier->train(dps);
  Parameters::select(previous_parameters);
}

bool ClassifierSetup::isActive(){
  return 0; // still empty
}

Descriptor ClassifierSetup::extract_(MyImage *image, 
				     bool makevisres, 
				     Image *representation){
  string previous_parameters = Parameters::get_current_name();
  Parameters::setUnique(parameters);
  FeatureExtractor *feature_extractor = FeatureExtractor::getInstance();
  int result = classifier->classify(&image->dp);
  Parameters::select(previous_parameters);
  Descriptor desc(1);
  desc[0] = (float) result;
  return desc;
}

string ClassifierSetup::getParameterName(){
  string previous_parameters = Parameters::get_current_name();
  Parameters::setUnique(parameters);
  long hash = Parameters::getInstance()->getCurrentHash();
  Parameters::select(previous_parameters);
  stringstream ss;
  ss << "activation_values_of_a" << classifier->get_name()
     << "with_settings:_" << hash;
  return ss.str();
}

} // features

namespace classification {

string ClassifierStack::get_name(){
  return "some classifierstack";
}

ClassifierStack::ClassifierStack(vector<features::ClassifierSetup> s) : 
  setups(s){
}

ClassifierStack::~ClassifierStack(){
  //delete classifier
}

vector<int> ClassifierStack::classify(std::vector<DataPoint*> points){
  return vector<int>();
}

int ClassifierStack::classify(DataPoint *point){
  vector<DataPoint*> points(1);
  points[0] = point;
  return classify(points)[0];
}

void ClassifierStack::train(vector<DataPoint*> files){
  // train every classifier In the Stack
  cout << "training each classifier in stack:..." << endl;
  for(size_t i = 0; i < setups.size(); ++i){
    cout << "training classifier " << i << endl;
    setups[i].train(files);
  }
  for(size_t i = 0; i < files.size(); i++){
    const DataPoint &current_datapoint = *files[i];
    for(size_t j = 0; j < setups.size(); j++){
      MyImage image(current_datapoint);
      Descriptor aap = setups[j].extract(&image);
      cout << "datapoint : " << i 
	   << ", features : " << j << ", descriptors:" ;
      copy(aap.begin(), aap.end(), ostream_iterator<int> (cout, ", "));
      cout << endl;
    }
  }
}


} // classification
} // vito
