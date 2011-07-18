#include "evaluation.h"
using namespace std;

namespace vito{
namespace evaluation{

string Stats::string(){
  std::stringstream ss;
  ss << "correct: " << correct << std::endl;
  ss << "handled: " << handled << std::endl;
  ss << "precision: " << (float) correct / (float) handled << std::endl;
  ss << "recall: " << (float) correct / (float) instances << std::endl;
  ss  << "---" << std::endl;
  return ss.str();
}

float Stats::getfmeasure(const float beta){
  float recall, precision;
  recall > 0 ? 
    recall = (float) correct / (float) instances : recall = 0 ;
  precision > 0 ? 
    precision = (float) correct / (float) handled : precision = 0 ;
  if(recall > 0 || precision > 0)
    return ((1 + beta * beta) * (precision * recall)) /
      (beta * beta * precision + recall);
  else
    return 0;
}


using classification::EstimationCollection;

map<int, Stats> Evaluation::getStatsMap(){
  return statsmap;
}



Evaluation::Evaluation(DataPointCollection &dps,
		       const EstimationCollection &estimations,
		       const float cutoff,
		       const float beta){
  recallevaluation = true;
  typedef EstimationCollection::const_iterator estit;
  assert(dps.size() == estimations.size());
  {
    instances = 0;
    ignored = 0;
    handled = 0;
    correct = 0;
    DataPointCollection::const_iterator dp = dps.begin(); 
    EstimationCollection::const_iterator est = estimations.begin();
    while(dp != dps.end() && est != estimations.end()){
      instances++;
      statsmap[dp->get_label()].instances++;
      if(est->likeliness < cutoff){
	ignored++;
      }
      else{
	statsmap[est->result].handled++;
	handled++;
	if(dp->get_label() == (size_t)est->result){
	  statsmap[est->result].correct++;
	  correct++;
	}
      }
      dp++; est++;
    }
    precision = (handled > 0)? (float) correct / (float) handled : 0;
    recall = (instances >0)? (float) correct / (float) instances : 0;
    fmeasure = (precision != 0 || recall != 0)?
      fmeasure = ((1 + beta * beta) * (precision * recall)) /
      (beta * beta * precision + recall) : 0;
  }
}

float Evaluation::getfmeasure(){
  return fmeasure;
}


Evaluation::Evaluation(){
}

Evaluation::Evaluation(DataPointCollection &dps, 
		       const LabelCollection &cls){
  instances = 0;
  correct = 0;
  for(vector<DataPoint>::const_iterator dp = dps.begin();
      dp != dps.end(); ++dp){
    map_total_to_label[dp->get_label()] = 0;
    map_correct_to_label[dp->get_label()] = 0;
  }
  if(dps.size() != cls.size())
    throw "bla";
  for(size_t i = 0; i < dps.size(); ++i){
    instances++;
    map_total_to_label[dps[i].get_label()]++;
    if((int) dps[i].get_label() == cls[i]){
      correct++;
      map_correct_to_label[dps[i].get_label()]++;
    }
    classificationmap[cls[i]].push_back(&dps[i]);
  }
  precision = (float) correct  / (float ) instances ;
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
  if(recallevaluation){
    cout << "recall: " << recall << endl;
    cout << "handled: " << handled << endl << endl;
  }
}

map<int, int> Evaluation::getCorrectMap(){
  return map_correct_to_label;
}
map<int, int> Evaluation::getTotalMap(){
  return map_total_to_label;
}

Evaluation::Evaluation(DataPointCollection &dps,
			const LabelCollection &classification,
			int one_class_t){
  cout << "one class evaluation!" << endl;
}


}}
