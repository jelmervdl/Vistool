#include "experiment.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using namespace boost::filesystem;

namespace vito{

using features::KMeansClusterHistogram;
typedef std::vector<Category*> categories;
using features::FeatureExtractor;
using features::Feature;
using classification::SVMClassifier;
using evaluation::Evaluation;
using classification::EstimationCollection;
using classification::Classifier;

namespace experiment{

struct SaveTo{
  size_t label;
  string original;
  float probability;
  SaveTo(size_t i, string s, float p = 1.0) : label(i), original(s), probability(p){};
  SaveTo(){};
};

void save(vector<SaveTo> operations, string dir,  Dataset &ds){
  for(vector<SaveTo>::iterator i = operations.begin();
      i != operations.end(); ++i){
    stringstream target;
    target << "result";
    if(!is_directory(system_complete(target.str())))
      create_directory(system_complete(target.str()));
    target << "/" << dir;
    if(!is_directory(system_complete(target.str())))
      create_directory(system_complete(target.str()));
    target << "/" <<  ds.getCatName(i->label);
    if(!is_directory(system_complete(target.str())))
      create_directory(system_complete(target.str()));
    stringstream pro_str;
    pro_str <<  i->probability;
    while(pro_str.str().size() < 10)
      pro_str << "0";
    target << "/" << pro_str.str() << "_" << operations.end() - i << " .jpg";
    cout << target.str() << endl;
    copy_file(system_complete(i->original), system_complete(target.str()));
  }	      
}

void classify(string original){
  Dataset ds = Dataset::getPrefferedDataset();
  path fullpath = system_complete(original);
  vector<DataPoint> dps = getDataPoints(fullpath, 0, original);
  SVMClassifier svm;
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  svm.train(fe->getExamples(ds.enabledPoints()));
  vector<Label> labels =  svm.classify(fe->getDescriptors(dps));
  vector<SaveTo> copyOperations; copyOperations.reserve(labels.size());
  
  vector<DataPoint>::iterator i = dps.begin();
  vector<Label>::iterator j = labels.begin();
  while(i != dps.end() && j != labels.end()){
    copyOperations.push_back(SaveTo(*j, i->get_image_url()));
    i++; 
    j++;
  }
  save(copyOperations, original, ds);
}

void estimate(string original, float cutoff){
  Dataset ds = Dataset::getPrefferedDataset();
  Parameters::getInstance()->saveInteger("svm_probability_real",1);
  path fullpath = system_complete(original);
  vector<DataPoint> dps = getDataPoints(fullpath, 0, original);
  SVMClassifier svm_;
  Classifier &svm = svm_;
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  svm.train(fe->getExamples(ds.enabledPoints()));
  EstimationCollection estimations =  svm.estimate(fe->getDescriptors(dps));
  vector<SaveTo> copyOperations; copyOperations.reserve(estimations.size());
  vector<DataPoint>::iterator i = dps.begin();
  EstimationCollection::iterator j = estimations.begin();
  while(i != dps.end() && j != estimations.end()){
    cout << i - dps.end() << endl;
    cout << j->likeliness << endl;
    if(j->likeliness > cutoff){
      cout << i - dps.end() << endl;
      copyOperations.push_back(SaveTo(j->result, i->get_image_url(), j->likeliness));
    }
    i++; 
    j++;
  }
  save(copyOperations, original, ds);
}

void recallExperiment(const string dataset_string){
  classification::EstimationCollection estimations;
  DataPointCollection datapoints;
  for(int i = 0; i < 100; i++){
    Parameters::getInstance()->saveInteger("svm_probability_real",1);
    Dataset dataset;  
    if(dataset_string == "")
      dataset = Dataset::getPrefferedDataset();
    else
      dataset = getDataSet(dataset_string);
    DataPointCollection dps,train,test;
    dps = dataset.enabledPoints();
    dataset.randomDataSplit(&train, &test, 0.5, true);
    datapoints.insert(datapoints.end(), test.begin(), test.end());
    SVMClassifier svm;
    classification::Classifier &classifier = svm;
    FeatureExtractor *fe = FeatureExtractor::getInstance();
    classifier.train(fe->getExamples(train));
    classification::EstimationCollection estimations_ = 
      classifier.estimate(fe->getDescriptors(test));
    estimations.insert(estimations.end(), 
		       estimations_.begin(), estimations_.end());
  } 
  float best = 0;
  float setting = 0;
  float beta = 0.25;
  for(float i = 0; i < 1.0; i+= 0.01){
    Evaluation evaluation(datapoints, estimations, i, beta);
    float fmeasure = evaluation.getStatsMap().begin()->second.getfmeasure(beta);
    cout << i << ": " << fmeasure << endl;
    if(fmeasure > best){
      best = fmeasure;
      setting = i;
    }
  }
  Evaluation evaluation(datapoints, estimations, setting, beta);
  cout << "chosen i: " <<setting << endl;
  evaluation.print();

  cout << endl << evaluation.getStatsMap().begin()->second.string()
       << "fmeasure: " << evaluation.getStatsMap().begin()->second.getfmeasure(beta) << endl;

}

float performExperiment(const string str, 
			const string dataset_string,
			const int repetitions,
			const size_t kDataPoints){
  cout << "performing experiment " << str << endl;
  Dataset dataset;
  if(dataset_string == "")
    dataset = Dataset::getPrefferedDataset();
  else
    dataset = getDataSet(dataset_string);
  float (*exp_func)(Dataset&, size_t) = 0;

  if(str == "svm") exp_func = &svm;
  if(str == "nn") exp_func = &nn;

  if(exp_func == 0){
    cout << "experiment not found" << endl;
    return 0.0;
  }if(str == "nn"){
    // optimize the k for nn
    Parameters *params = Parameters::getInstance();
    int orig = params->getiParameter("knn_classifier_k");
    vector<int> k_candidates;
    k_candidates.push_back(1);
    k_candidates.push_back(3);
    k_candidates.push_back(5);
    k_candidates.push_back(7);
    k_candidates.push_back(9);
    k_candidates.push_back(11);
    k_candidates.push_back(13);
    k_candidates.push_back(15);
    k_candidates.push_back(31);
    float max = 0;
    for(vector<int>::iterator i = k_candidates.begin();
	i != k_candidates.end(); ++i){
      params->saveInteger("knn_classifier_k", *i);
      Statistics temp_vals;
      for(int j = 0; j < 20; j++)
	temp_vals.push_back(exp_func(dataset, kDataPoints));
      cout << "k = " << *i << " : " << temp_vals.mean();
     cout << " +- " << temp_vals.std() << endl;
     if(temp_vals.mean() > max){
       max = temp_vals.mean();
       orig = *i;
     }
    }
   params->saveInteger("knn_classifier_k", orig);
  }
  Statistics values;
  
  for(int i = 0; i < repetitions; i++){
    values.push_back(exp_func(dataset, kDataPoints));
    //    if(i % 10 == 0)
    //  cout << "done with " << i << "currently: " << values.mean() << endl;
    //cout << "added: " << values[i] << " currentmean: " << values.mean() << endl;
  }
  cout << "k = " << Parameters::getInstance()->getiParameter("knn_classifier_k") << endl;
  cout << "mean: " << values.mean() << endl;
  cout << "std: " << values.std() << endl;
  cout << "with gamma " << Parameters::getInstance()->getfParameter("svm_gamma") << endl;
  cout << "with C " << Parameters::getInstance()->getfParameter("svm_C") << endl;
  return values.mean();
}

Dataset getDataSet(const string str){
  return Dataset::createDatasetByName(str);
}

Dataset abdullah2010(){
  Dataset dataset (string(DATASET_LOCATION) + "caltech101/");
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

float svm(Dataset &dataset, size_t datapoints){
  DataPointCollection train, test;
  dataset.randomDataSplit(&train, &test, 0.5, true, datapoints);

  //get Labels, Examples and Descriptors
  FeatureExtractor *fe = FeatureExtractor::getInstance();

  ExampleCollection training_examples = fe->getExamples(train);
  DescriptorCollection testing_descriptors = fe->getDescriptors(test);

  // train an svm
  classification::SVMClassifier svm;
  svm.train(training_examples);

  // classify the test
  LabelCollection result_labels = svm.classify(testing_descriptors);

  // evaluate the results
  Evaluation evaluation(test, result_labels);
  return evaluation.getPrecision();
}

float nn(Dataset &dataset, size_t datapoints){
  DataPointCollection train, test;
  dataset.randomDataSplit(&train, &test, 0.5, true, datapoints);

  //get Labels, Examples and Descriptors
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  ExampleCollection training_examples = fe->getExamples(train);
  DescriptorCollection testing_descriptors = fe->getDescriptors(test);

  // train an svm
  classification::NNClassifier svm;
  svm.train(training_examples);

  // classify the test
  LabelCollection result_labels = svm.classify(testing_descriptors);

  svm.clean();
  // evaluate the results
  Evaluation evaluation(test, result_labels);
  //evaluation.print();
  return evaluation.getPrecision();
}

void cluster(string dataset, string filename){
  Feature * feature = 0;
  {
    vector<Feature*> actives =  features::getActiveFeatures();
    if(actives.size() > 1){
      cout << "too many features active, 1 active feature is best" << endl;
      return;
    }if(actives.size() == 0){
      cout << "no active feature to cluster with!" << endl;
      return;
    }
    feature = actives[0];
  }
  Dataset dats = getDataSet(dataset);
  //features::KMeansClusterHistogram histogram(dats.enabledPoints(), feature);
  clustering::TrueClusterHistogram histogram(feature, dats.enabledPoints());
  //histogram.drawRandomPatches(dats.enabledPoints());
  histogram.save(filename + ".clustercenters");
  Parameters::getInstance()->saveXML(filename + ".xml");
}

}}
