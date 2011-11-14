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

float evaluateSVMAbdullah(){
  BestResult &best = *BestResult::getInstance();
  Statistics stats;
  int i = 0;
  Dataset ds = Dataset::getPrefferedDataset();  
  for(i = 1; i < 10; i++)
    stats.push_back(experiment::svm(ds));
  if(best.set == true){
    float exceed;
    do{
      stats.push_back(experiment::svm(ds));
      i++;
      exceed = studentTTest::exceedingChance(stats.mean(), stats.std(), i,
					     best.mean, best.std, best.size);
      cout << "exceeding chance of" 
	   << stats.mean() << " +- " << stats.std() << " " << i << "points"  << endl
	   << "to be over " << best.mean << " +- " << best.std  << " " << best.size << " points " << endl
	   << "is: " << exceed << endl;
    } while(exceed > 0.25 && exceed < 0.975 && i < 20);    
  }
  if(best.set != true || stats.mean() > best.mean){
    float std = stats.std();
    float target_std = 0.006;
    while(std * std > i * target_std * target_std  ){
      stats.push_back(experiment::svm(ds));
      std = stats.std();
      i++;
      cout << stats.mean() << " " << stats.std() << endl;
      cout << "target: " << target_std << " vs current: " << std << " -> " << std / (float) sqrt(i)<< endl;
    }
    cout << "after " << i << " rounds:" << endl
	 << "result: " << stats.mean() << " +- " << stats.std() << endl;
  }
  if(stats.mean() > best.mean || !best.set){
    best.mean = stats.mean();
    best.std = stats.std();
    best.size = stats.size();
    best.set = true;
  }
  return stats.mean();
}

float evaluateSVM(){   
  float result = 0.0;
  for(int i  = 0; i < 10; ++i){
    Dataset dataset = Dataset::createDatasetByName("bigclasses");
      /*
      ("../datasets/Caltech101/");
    dataset.enableCategory("airplanes");
    dataset.enableCategory("camera");
    dataset.enableCategory("car_side");
    dataset.enableCategory("cellphone");
    dataset.enableCategory("cup");
    dataset.enableCategory("helicopter");
    dataset.enableCategory("Motorbikes");
    dataset.enableCategory("scissors");
    dataset.enableCategory("umbrella");
    dataset.enableCategory("watch");
      */
    dataset.print();
    DataPointCollection points = dataset.enabledPoints();
    random_shuffle(points.begin(), points.end());
    SVMClassifier svm;
    FeatureExtractor *fe = FeatureExtractor::getInstance();
    DescriptorCollection examples = fe->getExamples(points);
    LabelCollection results = svm.crossvalidation(examples);
    cout << "done crossvalidating" << endl;
    Evaluation evaluation(points, results);
    cout << "done evaluating" << endl;
    result += evaluation.getPrecision();
  }
  return result / 10;
  }
/*
float evaluateOneClassSVM(){
  Dataset dataset("../datasets/Caltech101/");
  dataset.enableCategory("accordion");
  //dataset.enableCategory("anchor");
  //dataset.enableCategory("emu");
  //dataset.enableCategory("bass");
  //dataset.enableCategory("ant");
  DataPointCollection train, test;
  dataset.randomDataSplit(&train, &test, 0.5);
  FeatureExtractor::getInstance()->saveDescriptorsToFile(&dataset);

  OneClassSVM segsvm(0);
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  DescriptorCollection examples = fe->getExamples(train);
  segsvm.train(examples);

  dataset.disableCategory("accordion");
  dataset.enableCategory("emu");
  dataset.enableCategory("anchor");
  dataset.enableCategory("emu");
  dataset.enableCategory("bass");
  dataset.enableCategory("ant");
  DataPointCollection others = dataset.enabledPoints();

  others.insert(others.end(), test.begin(), test.end());
  vector<int> res(others.size());
  for(int i = 0; i < (int) others.size(); ++i)
    res[i] = segsvm.classify(others[i]);
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
*/
}}
