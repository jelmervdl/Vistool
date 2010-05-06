#include "main.h"
#include <locale>
#include <iomanip>

using std::sprintf;
using namespace vito;
using namespace vito::features;
using namespace vito::gui;
using namespace vito::optimization;
using namespace vito::classification;
using namespace std;

int main(int argc, char ** argv){ 
  if(argc > 1){
    Parameters * p = Parameters::getInstance();
    p->readFile((char *) "parameters.xml");
    string mode = argv[1];
    if(mode == "test"){
      testing::testAll();
      return 0;
    }if(mode == "gui"){
      start(1,argv);
      return 0;
    }if(mode == "optimize"){
      ParameterOptimization opt(&vito::optimization::evaluateSVM);
      opt.optimize();
    }
  }  
  Parameters *p = Parameters::getInstance();
  Dataset dataset("/Users/mauricemulder/workspace/datasets/caltech101/");
  p->readFile((char *) "parameters.xml");
  dataset.enableCategory("accordion");
  //dataset.enableCategory("anchor");
  dataset.enableCategory("emu");
  //dataset.enableCategory("bass");
  //dataset.enableCategory("ant");
  vector<DataPoint> train, test;
  dataset.randomDataSplit(&train, &test, 0.5);
  FeatureExtractor::getInstance()->saveDescriptorsToFile(&dataset);
  SVMClassifier segsvm;
  segsvm.train(ptr::ptrDeMorgan(&train));
  dataset.disableCategory("accordion");
  dataset.enableCategory("emu");
  vector<DataPoint> others = dataset.enabledPoints();
  others.insert(others.end(), test.begin(), test.end());
  vector<int> res = segsvm.classify(ptr::ptrDeMorgan(&test));
  int total, correct;
  for(int i = 0; i < (int) res.size(); i++){
    cout << test[i].get_label() << " " << res[i]<< endl;
    total++;
    if((int) test[i].get_label() == res[i])
      correct++;
  }
  cout << "total: " << total << endl << "correct: " << correct << endl
       << "precision " << correct / (double) total << endl;
  cout << "ya done" << endl;
  return 0;
}

