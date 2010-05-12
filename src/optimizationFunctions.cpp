#include "optimizationFunctions.h"

using std::vector;
using std::random_shuffle;
using std::cout;
using std::endl;

namespace vito{

using features::FeatureExtractor;
using classification::OneClassSVM;
using classification::SVMClassifier;
using evaluation::Evaluation;

namespace optimization{

float evaluateSVM(){   
  float result = 0.0;
  for(int i  = 0; i < 10; ++i){
    Dataset dataset("../datasets/Caltech101/");
    dataset.enableRandom(15);
    dataset.print();
    vector<DataPoint> points = dataset.enabledPoints();
    random_shuffle(points.begin(), points.end());
    SVMClassifier svm;
    vector<int> results = svm.crossvalidation(&points);
    cout << "done crossvalidating" << endl;
    Evaluation evaluation(&points, &results);
    cout << "done evaluating" << endl;
    result += evaluation.getPrecision();
  }
  return result / 10;
  }

float evaluateOneClassSVM(){
  Dataset dataset("../datasets/Caltech101/");
  dataset.enableCategory("accordion");
  //dataset.enableCategory("anchor");
  //dataset.enableCategory("emu");
  //dataset.enableCategory("bass");
  //dataset.enableCategory("ant");
  vector<DataPoint> train, test;
  dataset.randomDataSplit(&train, &test, 0.5);
  FeatureExtractor::getInstance()->saveDescriptorsToFile(&dataset);
  OneClassSVM segsvm(0);
  segsvm.train(ptr::ptrDeMorgan(&train));
  dataset.disableCategory("accordion");
  dataset.enableCategory("emu");
  dataset.enableCategory("anchor");
  dataset.enableCategory("emu");
  dataset.enableCategory("bass");
  dataset.enableCategory("ant");
  vector<DataPoint> others = dataset.enabledPoints();

  others.insert(others.end(), test.begin(), test.end());
  vector<int> res(others.size());
  for(int i = 0; i < (int) others.size(); ++i)
    res[i] = segsvm.classify(&others[i]);
  int total = 0, correct = 0, incorrect = 0;
  for(int i = 0; i < (int) res.size(); i++){
    //cout << others[i].get_label() << " " << res[i] 
      //<<  " the values " << segsvm.getValue(&others[i])[0] << endl;
    total++;
    if(res[i] == 1)
      if((int) others[i].get_label() == 0)
	correct++;
      else
	incorrect++;
  }
  double precision = correct / (double) (incorrect + correct);
  double recall = correct / (double) total;
  double f_score = 0;
  if(precision + recall > 0)
     f_score = (2 * precision * recall) / (precision + recall);

  cout << "total: " << total << endl 
       << "correct: " << correct << endl
       << "incorrect: " << incorrect << endl
       << "precision: " << correct / (double) (incorrect + correct) << endl
       << "recall: " << correct / (double) total << endl
       << "f-score: " << f_score << endl;
  cout << "ya done" << endl;
  return f_score;
}

}}
