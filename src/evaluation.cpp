#include "evaluation.h"
using namespace std;

namespace vito{
namespace evaluation{

Evaluation::Evaluation(vector<DataPoint*> &dps, 
		       vector<int> &cls){
  instances = 0;
  correct = 0;
  for(size_t dp_idx = 0; dp_idx < dps.size(); ++dp_idx){
    DataPoint*&dp = dps[dp_idx];
    map_total_to_label[dp->get_label()] = 0;
    map_correct_to_label[dp->get_label()] = 0;
  }
  if(dps.size() != cls.size())
    throw 1;
  for(size_t i = 0; i < dps.size(); ++i){
    instances++;
    map_total_to_label[dps[i]->get_label()]++;
    cout << ".";
    if((int) dps[i]->get_label() == cls[i]){
      correct++;
      map_correct_to_label[dps[i]->get_label()]++;
    }
    classificationmap[ cls[i] ].push_back(dps[i]);
  }
  precision = (float) correct  / (float ) instances ;
  cout << instances << endl;

}


Evaluation::Evaluation(vector<DataPoint> * dps, vector<int> * cls){
  instances = 0;
  correct = 0;
  for(vector<DataPoint>::iterator dp = dps->begin();
      dp != dps->end(); ++dp){
    map_total_to_label[dp->get_label()] = 0;
    map_correct_to_label[dp->get_label()] = 0;
  }
  cout << "dps is of size " << dps->size() 
       << " and cls of size " << cls->size() << endl;
  if(dps->size() != cls->size())
    throw "bla";
  for(size_t i = 0; i < dps->size(); ++i){
    instances++;
    map_total_to_label[dps->at(i).get_label()]++;
    cout << ".";
    if((int) dps->at(i).get_label() == cls->at(i)){
      correct++;
      map_correct_to_label[dps->at(i).get_label()]++;
    }
    classificationmap[cls->at(i)].push_back(&dps->at(i));
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

vector<DataPoint *> Evaluation::getInstancesClassifiedAs(int cl){
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

}}
