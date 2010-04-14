#include "main.h"
#include "multiton.h"
 
using VisionToolGUI::start;
using parameter_optimization::ParameterOptimization;
using VisionToolClassification::SVMClassifier;


float trick(){
   
  Parameters *parameters = Parameters::getInstance();
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

int main(int argc, char ** argv){
  if(argc > 1){
    string aap = argv[1];
    if(aap == "test"){
      testing::testAll();
      return 0;
    }
  }  
  Parameters * p = Parameters::getInstance();
  p->readFile((char *) "parameters.xml");

  //ParameterOptimization opt(&trick);
  //opt.optimize();
  start(argc, argv);
  return 0;
}

void printLibraries(){
  cout << "hi" << endl;
}
