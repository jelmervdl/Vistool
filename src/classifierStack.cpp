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

ClassifierSetup::ClassifierSetup(Classifier *c, string xmlfile) : 
  Setup(xmlfile), classifier(c){
  string old_name = Parameters::get_current_name();
  parameters = Parameters::getUnique();
  Parameters::setUnique(parameters);
  Parameters::getInstance()->readFile("parameters.xml");
  Parameters::getInstance()->readFile(xmlfile.c_str());
  Parameters::select(old_name);
}

ClassifierSetup::ClassifierSetup( Classifier *c) : 
  Setup("parameters.xml"), classifier(c){
  string old_name = Parameters::get_current_name();
  parameters = Parameters::getUnique();
  Parameters::setUnique(parameters);
  Parameters::select(old_name);
}

void ClassifierSetup::train(const ExampleCollection &descriptors){
  string previous_parameters = Parameters::get_current_name();
  Parameters::setUnique(parameters);
  cout << "current hashable string is: " 
       << Parameters::getInstance()->getHashableString() << endl;
  cout << "the current hash is: " 
       << Parameters::getInstance()->getCurrentHash() << endl;
  classifier->train(descriptors);
  Parameters::select(previous_parameters);
}

bool ClassifierSetup::isActive(){
  return Parameters::getInstance()->getiParameter(getParameterName()) > 0; 
}

Setup::Setup(std::string xmlfile) : name(xmlfile){
  string old_name = Parameters::get_current_name();
  parameters = Parameters::getUnique();
  Parameters::setUnique(parameters);
  Parameters::getInstance()->readFile(xmlfile);
  Parameters::getInstance()->readFile("parameters.xml");
  Parameters::getInstance()->readFile(xmlfile);
  Parameters::select(old_name);
  previous = "0";
}

std::string Setup::get_name(){
  return name;
}

void Setup::push(){
  if(previous != "0")
    Parameters::select(previous);
  previous = Parameters::get_current_name();
  Parameters::setUnique(parameters);
  return;
}

void Setup::pop(){
  if(previous != "0")
    Parameters::select(previous);
  previous = "0";
}

SetupFeature::SetupFeature() {}
SetupFeature::SetupFeature(std::vector<Setup> setups) 
  : std::vector<Setup>(setups){
}

std::string SetupFeature::getParameterName(){
  typedef std::vector<Setup>::iterator setup_it;
  std::stringstream ss;
  ss << "naive_combining";
  for(setup_it i = begin(); i != end(); ++i)
    ss << i->get_name();
  return ss.str();
}

bool SetupFeature::isActive(){
  return Parameters::getInstance()->getiParameter("feature_" + 
						  getParameterName()) > 0;
}

Descriptor SetupFeature::extract_(MyImage *Image, 
				  bool makeVisualRepresentation, 
				  Magick::Image * representation){
  Descriptor ret;
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  typedef std::vector<Setup>::iterator su_it;
  cout << "extracting stuff from combined features" << endl;
  cout << "there are " << size() << "features to combine.." << endl;
  for(su_it i = begin(); i != end(); ++i){
    i->push();
    cout << "current parameter list comes from"
	 << Parameters::getInstance()->getFile() << endl; 
    Descriptor additive = fe->getDescriptor(Image->getDataPoint());
    cout << "adding additive of size " << additive.size() << endl;
    ret = ret + additive;
    i->pop();
  }
  cout << "returning combination of size " << ret.size() << endl;
  return ret;
}



Descriptor ClassifierSetup::extract_(MyImage *image, 
				     bool makevisres, 
				     Image *representation){
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  push();
  Descriptor des = fe->getDescriptor(image->getDataPoint());
  int result =  classifier->classify(des);
  pop();
  Descriptor ret(1);
  ret[0] = (float) result;
  return ret;
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


void NaiveStackFeatures::add_to(std::vector<Feature*> &features){
  typedef std::vector<SetupFeature>::iterator sf_it;
  for(sf_it i = begin(); i != end(); ++i)
    features.push_back((Feature *) &(*i));
}

SVMActivationSetup::SVMActivationSetup(std::string setting) : 
  Setup(setting){}

std::string SVMActivationSetup::getFile(){
  return origin;
}

void SVMActivationSetup::train(DataPointCollection dps){
  push();
  ExampleCollection examples =
    FeatureExtractor::getInstance()->getExamples(dps);
  svm.train(examples);
  pop();
}

Descriptor SVMActivationSetup::getActivation(DataPoint dp){
  vector<double> dubs =
    svm.getValues(FeatureExtractor::getInstance()->getDescriptor(dp));
  Descriptor desc;
  for(vector<double>::iterator i = dubs.begin(); i != dubs.end(); ++i)
    desc.push_back(*i);
  return desc;
}

bool SVMStack::isActive(){
  return Parameters::getInstance()->getiParameter("feature_" +
						  getParameterName()) > 0;
}

std::string SVMStack::getParameterName(){
  stringstream name;
  name << "svmstack_of";
  for(SVMStack::iterator i = begin(); i != end(); ++i)
    name << i->getFile() << "_";
  return name.str();
}

Descriptor SVMStack::extract_(MyImage *image, 
			      bool makevisrep,
			      Magick::Image rep){
  Descriptor desc;
  for(SVMStack::iterator i = begin(); i != end(); ++i)
    desc = desc + i->getActivation(image->getDataPoint());
  return desc;
}  

void SVMStack::train(DataPointCollection dps){
  for(SVMStack::iterator i = begin(); i != end(); ++i)
    i->train(dps);
}
} // features

namespace classification {

std::string SVMStack::get_name(){
  std::stringstream ss;
  ss << "svm_stack";
  for(SVMStack::iterator i = begin(); i != end(); ++i)
    ss << "_" << i->getFile();
  return ss.str();
}

void SVMStack::train(const ExampleCollection &examples){
  //for(SVMStack::iterator i = begin(); i != end(); ++i)
    //i->train(examples);
  svm.train(getStackExamples(examples));
}

Label SVMStack::classify(const Descriptor &descriptor){
  return svm.classify(getStackResults(descriptor));
}

ExampleCollection SVMStack::getStackExamples(const ExampleCollection &examples){
  ExampleCollection stack_examples;
  DescriptorCollection stack_result = 
    getStackResults(DescriptorCollection(examples));

  assert(examples.size() == stack_result.size());

  DescriptorCollection::iterator d;
  ExampleCollection::const_iterator e;
  for( d =stack_result.begin(),	e = examples.begin();
      d != stack_result.end() && e != examples.end();
      ++e, ++d)
    stack_examples.push_back(Example(*d, e->get_label()));
  return stack_examples;
}

DescriptorCollection SVMStack::getStackResults(const DescriptorCollection & dc){
  DescriptorCollection collection;
  for(DescriptorCollection::const_iterator i = dc.begin(); i != dc.end(); ++i)
    collection.push_back(getStackResults(*i));
  return collection;
}

 Descriptor SVMStack::getStackResults(const Descriptor &descriptor){
  Descriptor stack_result;
  //for(SVMStack::iterator i = begin(); i != end(); ++i)
  //stack_result = stack_result + i->getActivation(descriptor);
  return descriptor;
 }


ClassifierStack::ClassifierStack(vector<features::ClassifierSetup> s) : 
  setups(s){
}

ClassifierStack::~ClassifierStack(){
  //delete classifier
}

string ClassifierStack::get_name(){
  return "some classifierstack";
}

int ClassifierStack::classify(const Descriptor &descriptor){
  return 0;
}

void ClassifierStack::train(const ExampleCollection &examples){
  // train every classifier In the Stack
  cout << "training each classifier in stack:..." << endl;
  for(size_t i = 0; i < setups.size(); ++i){
    cout << "training classifier " << i << endl;
    setups[i].train(examples);
  }
  // train the stacktop classifier
}

} // classification
} // vito
