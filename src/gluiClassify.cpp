#include "gluiClassify.h"

void train(){
  ToolState &state = *ToolState::getInstance();
  extractFeatures();
  state.train_data.clear();
  state.test_data.clear();
  state.current_db->randomDataSplit(&state.train_data, &state.test_data, 0.5, true);
  delete state.current_classifier;
  state.current_classifier = new NNClassifier();
  state.current_classifier->train(&state.train_data);
  for(vector<int>::iterator cl = state.current_classes.begin(); 
      cl != state.current_classes.end(); 
      cl++)
    state.selected_class_listbox->delete_item(*cl);
  state.current_classes.clear();
  vector<Category*> enabs = state.current_db->getEnabled();
  for(size_t i = 0; i <  enabs.size(); ++i){
	state.selected_class_listbox->add_item(enabs[i]->getLabel(), 
					 enabs[i]->getName().c_str());
	state.current_classes.push_back(enabs[i]->getLabel());
    }
}

void classify(){
  ToolState &state = *ToolState::getInstance();
  if(state.current_classifier == NULL)
    train();
  state.test_result = state.current_classifier->classify(&state.test_data);
  delete state.current_evaluation;
  state.current_evaluation = new Evaluation(&state.test_data, &state.test_result);
  viewDataset();
  showStatistics();
}
