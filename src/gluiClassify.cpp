#include "gluiClassify.h"

namespace vito{
namespace gui{

using classification::getExistingClassifier;
using classification::Classifier;
using classification::NNClassifier;
using classification::SVMClassifier;

void train(){
  cout << "yeah" << endl;
  ToolState &state = *ToolState::getInstance();
  extractFeatures();
  state.train_data.clear();
  state.test_data.clear();
  state.current_db->randomDataSplit(&state.train_data, &state.test_data, 0.5, true);
  state.current_classifier = getExistingClassifier(state.enabled_classifier);
  cout << "yeah" << endl;
  state.current_classifier->train(&state.train_data);
  cout << "yeaoh" << endl;
  for(vector<int>::iterator cl = state.current_classes.begin(); 
      cl != state.current_classes.end(); 
      cl++)
    state.selected_class_listbox->delete_item(*cl);
  state.current_classes.clear();
  vector<Category*> enabs = state.current_db->getEnabled();
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
  vector<DataPoint> enabsp = state.current_db->enabledPoints();
  state.test_result = state.current_classifier->classify(&state.test_data);
  delete state.current_evaluation;
  if(!state.current_classifier->single_class())
    state.current_evaluation = new Evaluation(&state.test_data, 
					      &state.test_result);
  else
    state.current_evaluation = new Evaluation(&state.test_data, 
					      &state.test_result,
					      state.one_class_target);
  viewDataset();
  showStatistics();
}

void non_set_classify(){
  ToolState &state = *ToolState::getInstance();
  if(state.current_classifier == NULL)
    train();
  vector<DataPoint*> points = state.current_db->enabledDataPoints(false);
  state.test_result = state.current_classifier->classify(points);
  delete state.current_evaluation;
  state.current_evaluation = new Evaluation(points, state.test_result);
  viewDataset();
  showStatistics();
}

}}
