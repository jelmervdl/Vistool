#include "optimizationFunctions.h"

using std::vector;
using std::random_shuffle;
using std::cout;
using std::endl;

namespace vito{

using classification::SVMClassifier;
using evaluation::Evaluation;

namespace optimization{

float evaluateSVM(){   
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


}}
