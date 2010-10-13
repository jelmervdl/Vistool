#include "gluiEvaluate.h"

using std::cout;
using std::endl;
using std::vector;
using std::stringstream;
using std::map;

namespace vito{
namespace gui{

using classification::getExistingClassifier;
using classification::NNClassifier;
using classification::SVMClassifier;
using classification::Classifier;


void evaluateClassifier(){
  train();
  classify();
}

void crossValidate(){
  ToolState &state = *ToolState::getInstance();

  state.train_data.clear();
  state.test_data.clear();
  state.current_classifier = getExistingClassifier(state.enabled_classifier);
  DataPointCollection enabsp = state.current_db.enabledPoints();
  random_shuffle(enabsp.begin(), enabsp.end());
  state.train_data = enabsp;
  state.test_data = enabsp;
  ExampleCollection examples =
    features::FeatureExtractor::getInstance()->getExamples(state.train_data);
  state.test_result = state.current_classifier->crossvalidation(examples);
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
  cout << "size of enabsp " << enabsp.size() << " and train: " 
       << state.train_data.size() << " and the test results " 
       << state.test_result.size() << endl;
  state.current_evaluation = Evaluation(state.train_data, state.test_result);
  viewDataset();
  showStatistics();
}

void showStatistics(){
  ToolState &state = *ToolState::getInstance();
  GLUI *&stats = state.stats;
  Evaluation &current_evaluation = state.current_evaluation;
  Dataset &current_db = state.current_db;
  if(stats != NULL)
    stats->close();
  stats = GLUI_Master.create_glui("statistics", 0, 1125, 0);
  {
    stringstream strstr;
    strstr  << "Instances: " << current_evaluation.getInstances() << endl;
    stats->add_statictext(strstr.str().c_str());
  } {
    stringstream strstr;
    strstr  << "Correct: " << current_evaluation.getCorrect() << endl;
    stats->add_statictext(strstr.str().c_str());
  } {
     stringstream strstr;
     strstr  << "Performance: " << current_evaluation.getPrecision() << endl;
     stats->add_statictext(strstr.str().c_str());
  }
   // show confusion info
  map<int, int> cormap = current_evaluation.getCorrectMap();
  map<int, int> totmap = current_evaluation.getTotalMap();
  int count = 0;
  for(map<int, int>::iterator it = cormap.begin();
      it!= cormap.end(); ++it){
    stringstream strstr;
     strstr  << (*it).first << "." <<  current_db.getCatName((*it).first) 
	     << " " << (*it).second <<  "/" << totmap[(*it).first] << endl;
     stats->add_statictext(strstr.str().c_str());
     count ++;
     if(count % 10 == 0)
       stats->add_column();
  }
  
 }
}}
