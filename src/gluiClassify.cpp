#include "gluiClassify.h"

namespace vito{
namespace gui{

using classification::getExistingClassifier;
using classification::Classifier;
using classification::NNClassifier;
using classification::SVMClassifier;

void train(){
  ToolState &state = *ToolState::getInstance();
  // create train and test set
  state.train_data.clear();
  state.test_data.clear();
  state.current_db.randomDataSplit(&state.train_data, &state.test_data,
				   0.5, true); // make a 50/50 split
  // get Active classification Object
  state.current_classifier = getExistingClassifier(state.enabled_classifier);
  ExampleCollection examples = 
    features::FeatureExtractor::getInstance()->getExamples(state.train_data);
  cout << "training points:" << endl;
  examples.print();
  state.current_classifier->train(examples);
  for(vector<int>::iterator cl = state.current_classes.begin(); 
      cl != state.current_classes.end(); 
      cl++)
    state.selected_class_listbox->delete_item(*cl);
  state.current_classes.clear();
  vector<Category*> enabs = state.current_db.getEnabled();
  for(size_t i = 0; i <  enabs.size(); ++i){
	state.selected_class_listbox->add_item(enabs[i]->get_label(), 
					 enabs[i]->get_name().c_str());
	state.current_classes.push_back(enabs[i]->get_label());
    }

}

void classify(){
  ToolState &state = *ToolState::getInstance();
  if(state.current_classifier == NULL)
    train();
  ExampleCollection examples = 
    features::FeatureExtractor::getInstance()->getExamples(state.test_data);
  cout << "test points:" << endl;
  examples.print();
  DescriptorCollection descriptors =
    features::FeatureExtractor::getInstance()->getDescriptors(state.test_data);
  state.test_result = state.current_classifier->classify(descriptors);
  if(!state.current_classifier->single_class())
    state.current_evaluation = Evaluation(state.test_data, 
					  state.test_result);
  else
    state.current_evaluation = Evaluation(state.test_data, 
					  state.test_result,
					  state.one_class_target);
  viewDataset();
  showStatistics();
}

void non_set_classify(){
  ToolState &state = *ToolState::getInstance();
  if(state.current_classifier == NULL)
    train();
  DataPointCollection datapoints = state.current_db.enabledPoints(false);
  DescriptorCollection descriptors = 
    features::FeatureExtractor::getInstance()->getDescriptors(datapoints);
  state.test_result = state.current_classifier->classify(descriptors);
  state.current_evaluation = Evaluation(datapoints, state.test_result);
  viewDataset();
  showStatistics();
}

}}
