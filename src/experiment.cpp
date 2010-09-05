#include "experiment.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

namespace vito{

typedef std::vector<Category*> categories;
// vito namespace use:
using features::FeatureExtractor;
using classification::SVMClassifier;
using evaluation::Evaluation;
namespace experiment{

void performExperiment(const string str, const int repetitions){
  cout << "performing experiment " << str << endl;
  float (*exp_func)() = 0;
  if(str == "abdullah2010"){
    exp_func = &abdullah2010;
  }
  if(exp_func == 0){
    cout << "experiment not found" << endl;
    return;
  }else{
    Statistics values;
    for(int i = 0; i < repetitions; i++)
      values.push_back(exp_func());
    cout << "mean: " << values.mean() << endl;
    cout << "std: " << values.std() << endl;
  }
}



float abdullah2010(){
  // select correct dataset
  Dataset dataset("../datasets/Caltech101/");
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
  dataset.print();

  // get dataPoints
  DataPointCollection train, test;
  dataset.randomDataSplit(&train, &test, 0.5, true, 30);

  cout << train.size() << " train points" << endl;
  cout << test.size() << " test points" << endl;


  //get Labels, Examples and Descriptors
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  ExampleCollection training_examples = fe->getExamples(train);
  DescriptorCollection testing_descriptors = fe->getDescriptors(test);


  // train an svm
  SVMClassifier svm;
  svm.train(training_examples);

  // classify the test
  LabelCollection result_labels = svm.classify(testing_descriptors);

  // evaluate the results
  Evaluation evaluation(test, result_labels);
  evaluation.print();
  return evaluation.getPrecision();
}

}}
