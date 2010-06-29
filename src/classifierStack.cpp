#include "classifierStack.h"

using std::stringstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using Magick::Image;

namespace vito{

using classification::Classifier;
using features::Feature;

namespace features {

ClassifierSetup::ClassifierSetup(Classifier *c, string xmlfile) : classifier(c){
  string old_name = Parameters::get_current_name();
  parameters = Parameters::getUnique();
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
  //FeatureExtractor *feature_extractor = FeatureExtractor::getInstance();
  //vector<float> descriptor = feature_extractor->get
  Parameters::select(previous_parameters);
  Descriptor desc;
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
  //for(size_t i = 0; i < features.size(); i++)
  //  ss << features[i]->getParameterName() << "_";
  return ss.str();
}

}


namespace classification {


}

}
