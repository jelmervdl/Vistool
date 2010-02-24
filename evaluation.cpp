#include "evaluation.h"
using namespace std;

Evaluation::Evaluation(vector<DataPoint> * dps, vector<int> * cls){
  if(dps->size() != cls->size())
    throw 1;
  for(size_t i; i < dps->size(); ++i){
    instances++;
    if((int) dps->at(i).getLabel() == cls->at(i))
      correct++;
    classificationmap[cls->at(i)].push_back(&dps->at(i));
  }
}

size_t Evaluation::getCorrect(){
  return correct;
}
size_t Evaluation::getInstances(){
  return instances;
}
float Evaluation::getRecall(){
  return recall;
}
float Evaluation::getPrecision(){
  return precision;
}
float Evaluation::getTval(){
  return tval;
}

vector<DataPoint *> Evaluation::getInstancesClassifiedAs(int cl){
  return classificationmap[cl];
}
