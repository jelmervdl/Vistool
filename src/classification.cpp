#include "classification.h"

using std::cout;
using std::endl;
using std::vector;

namespace vito{
namespace classification{

using vito::gui::ToolState;

vector<Classifier*> getExistingClassifiers(){
  vector<Classifier*> classifiers;
  classifiers.push_back(NNClassifier::getInstance());
  classifiers.push_back(SVMClassifier_::getInstance());
  classifiers.push_back(SegmentSVM::getInstance());
  classifiers.push_back(OneClassSVM::getInstance());
  OneClassSVM::getInstance()->set_truth_label( ToolState::getInstance()->
					       one_class_target);
  return classifiers;
}

Classifier *getExistingClassifier(int i){
  return getExistingClassifiers()[i];
}

}}

