#include "evaluation.h"
using namespace std;

namespace vito{
namespace evaluation{

Evaluation::Evaluation(){
}

Evaluation::Evaluation(const DataPointCollection &dps, 
		       const LabelCollection &cls){
  instances = 0;
  correct = 0;
  for(vector<DataPoint>::const_iterator dp = dps.begin();
      dp != dps.end(); ++dp){
    map_total_to_label[dp->get_label()] = 0;
    map_correct_to_label[dp->get_label()] = 0;
  }
  cout << "dps is of size " << dps.size() 
       << " and cls of size " << cls.size() << endl;
  if(dps.size() != cls.size())
    throw "bla";
  for(size_t i = 0; i < dps.size(); ++i){
    instances++;
    map_total_to_label[dps[i].get_label()]++;
    cout << ".";
    if((int) dps[i].get_label() == cls[i]){
      correct++;
      map_correct_to_label[dps[i].get_label()]++;
    }
    classificationmap[cls[i]].push_back(&dps[i]);
  }
  precision = (float) correct  / (float ) instances ;
  cout << instances << endl;
}

size_t Evaluation::getCorrect(){
  return correct;
}
size_t Evaluation::getInstances(){
  return instances;
}
float Evaluation::getPrecision(){
  return precision;
}

vector<const DataPoint *> Evaluation::getInstancesClassifiedAs(int cl){
  return classificationmap[cl];
}
void Evaluation::print(){
  cout << "correct: " << correct << endl;
  cout << "total  : " << instances << endl;
  cout << "precision: " << precision << endl;
}

map<int, int> Evaluation::getCorrectMap(){
  return map_correct_to_label;
}
map<int, int> Evaluation::getTotalMap(){
  return map_total_to_label;
}

Evaluation::Evaluation(const DataPointCollection &dps,
			const LabelCollection &classification,
			int one_class_t){
  cout << "one class evaluation!" << endl;
}


}}
