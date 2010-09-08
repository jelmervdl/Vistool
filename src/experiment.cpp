#include "experiment.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

namespace vito{

using features::KMeansClusterHistogram;

typedef std::vector<Category*> categories;
using features::FeatureExtractor;
using features::Feature;
using classification::SVMClassifier;
using evaluation::Evaluation;
namespace experiment{

float performExperiment(const string str, 
			const string dataset_string,
			const int repetitions){
  cout << "performing experiment " << str << endl;

  Dataset dataset = getDataSet(dataset_string);
  float (*exp_func)(Dataset&) = 0;

  if(str == "svm") exp_func = &svm;
  if(str == "clustering"){
    exp_func = &clustering;
    vector<Dataset> splits = dataset.split();
    KMeansClusterHistogram cluster(splits[0].enabledPoints(), 
				   features::mpeg7::EdgeHistogram::getInstance());
    dataset = splits[1];
  }

 if(exp_func == 0){
    cout << "experiment not found" << endl;
  }else{
    Statistics values;
    for(int i = 0; i < repetitions; i++)
      values.push_back(exp_func(dataset));
    cout << "mean: " << values.mean() << endl;
    cout << "std: " << values.std() << endl;
    return values.mean();
  }
  return 0.0;
}

Dataset getDataSet(const string str){
  if(str == "abdullah2010")
    return abdullah2010();
  return Dataset();
}

Dataset abdullah2010(){
  Dataset dataset ("../datasets/Caltech101/");
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
  return dataset;
}

float svm(Dataset &dataset){
  DataPointCollection train, test;
  dataset.randomDataSplit(&train, &test, 0.5, true, 30);

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

Feature* getClusteringFeature(const Dataset &dataset){

}

float clustering(Dataset &dataset){
  vector<Dataset> datasets = abdullah2010().split();
  KMeansClusterHistogram cluster(datasets[0].enabledPoints(), 
				 features::mpeg7::EdgeHistogram::getInstance());  

  return 0.0;
}

}}
