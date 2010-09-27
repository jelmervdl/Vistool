#include "main.h"
using std::sprintf;
using namespace vito;
using namespace vito::features;
using namespace vito::gui;
using namespace vito::optimization;
using namespace vito::classification;
using namespace std;

void testClassifierStack(){
  Dataset dataset("/Users/mauricemulder/workspace/datasets/caltech101/");
  dataset.enableCategory("accordion");
  dataset.enableCategory("emu");
  DataPointCollection train, test;
  dataset.randomDataSplit(&train, &test);
  vector<ClassifierSetup> to_stack;
  to_stack.push_back(ClassifierSetup (new NNClassifier, 
				      "standard_color_histogram.xml") );
  to_stack.push_back(ClassifierSetup(new NNClassifier, 
				     "standard_mpeg7_edge_histogram.xml"));
  ClassifierStack classifier_stacker(to_stack);
  FeatureExtractor *fe = FeatureExtractor::getInstance();
  {
    ExampleCollection examples = fe->getExamples(train);
    classifier_stacker.train(examples);
  }
  LabelCollection result;
  {
    DescriptorCollection descriptors = fe->getDescriptors(test);
    result = classifier_stacker.classify(descriptors);
  }
  //Evaluation eval(&test, &result);  
}

void resizeExperiment(){
  Magick::Geometry geo = Magick::Geometry(100,100);
  Magick::Image magick = Magick::Image("beaver_resize.jpg");
  Magick::Blob blob;
  magick.write(&blob);
  for(int i = 0; i < 5000; ++i){
    Magick::Image magick2(blob);
    //magick2.resize(geo);
    Magick::Blob blob2;
    magick2.write(&blob2);
  }
}

int main(int argc, char ** argv){ 
  srand(time(NULL));
  vector<string> arguments;
  Parameters *p = Parameters::getInstance();
  p->readFile("parameters.xml");
  // get out the options
  for(int i = 1; i < argc; i++){
    if(argv[i][0] == '-' && argc > (i + 1) ){
      string option_name = string(argv[i]).substr(1);
      string value = argv[i + 1];
      i++;
      if(option_name == "p"){
	p->clear();
	p->readFile(value);
      }else{
	return 1;
      }
    }else{
      arguments.push_back(argv[i]);
    }
  }
  // get actual commands
  vector<string>::iterator
    arg = arguments.begin(),
    end = arguments.end();
  if(arg == end) {
    return 1;
  }
  if(*arg == "test"){
    testing::testAll();
    return 0;
  }
  if(*arg == "gui"){
    start(1,argv);
    return 0;
  }
  if(*arg == "optimize"){
    ParameterOptimization opt(&vito::optimization::evaluateSVMAbdullah);
    opt.optimize();
    return 0;
  }
  if(*arg == "experiment"){
    arg++;
    if(arg == end){
      cout << "experiment type needed!" << endl;
      return 1;
    }
    string type = *arg;
    arg++;
    if(arg == end){
      experiment::performExperiment(type);
      return 0;
    }
    string dataset = *arg;
    arg++;
    if(arg == end){
      experiment::performExperiment(type, dataset);
      return 0;
    }
    int reps = atoi(arg->c_str());
    arg++;
    if(arg == end){
	  experiment::performExperiment(type, dataset, reps);	  
	  return 0;
    }
  }
  cout << "not a valid command" << endl;
  return 1;
}

void one_class_test(){
  const unsigned int nFeatures = 3;
  cout << "testing the one_class test" << endl;
  cout << "setting parameters";
  svm_parameter parameters;
  parameters.svm_type = ONE_CLASS;
  parameters.kernel_type = RBF;
  parameters.gamma =  (1.0 / 3.0) * 0.001;
  parameters.nu = 0.5;
  parameters.cache_size = 1024;
  parameters.C = 1;
  parameters.eps = 0.001;
  cout << " ... done!" << endl;


  cout << "constructing problem" << endl;
  svm_problem problem;
  const unsigned int nProblems = 3;
  problem.l = nProblems;
  problem.x = new svm_node*[nProblems];
  problem.y = new double[nProblems];

  problem.y[0] = 1;
  problem.x[0] = new svm_node[nFeatures + 1];
  problem.x[0][0].index = 0;
  problem.x[0][0].value = 1.5;

  problem.x[0][1].index = 1;
  problem.x[0][1].value = 2.5;

  problem.x[0][2].index = 2;
  problem.x[0][2].value = 3.5;

  problem.x[0][nFeatures].index = -1;
  problem.x[0][nFeatures].value = 0.0;

  problem.y[1] = 1;
  problem.x[1] = new svm_node[nFeatures + 1];
  problem.x[1][0].index = 0;
  problem.x[1][0].value = 1.4;

  problem.x[1][1].index = 1;
  problem.x[1][1].value = 2.4;

  problem.x[1][2].index = 2;
  problem.x[1][2].value = 3.4;

  problem.x[1][nFeatures].index = -1;
  problem.x[1][nFeatures].value = 0.0;
  
  problem.y[2] = 7;
  problem.x[2] = new svm_node[nFeatures + 1];
  problem.x[2][0].index = 0;
  problem.x[2][0].value = 0.6;

  problem.x[2][1].index = 1;
  problem.x[2][1].value = 1.6;

  problem.x[2][2].index = 2;
  problem.x[2][2].value = 1.6;

  problem.x[2][nFeatures].index = -1;
  problem.x[2][nFeatures].value = 0.0;
  
  cout << " ... done!" << endl;
  vito::print::print_svm_problem(&problem);
  svm_model *model = svm_train(&problem, &parameters);

  for(int i = 0; i < 20; ++i){
  svm_node *test = new svm_node[nFeatures + 1];
  test[0].index = 0;
  test[0].value = 0.6;

  test[1].index = 1;
  test[1].value = 1.6;

  test[2].index = 2;
  test[2].value = 1.5 + (float) i / 10.0;

  test[nFeatures].index = -1;
  test[nFeatures].value = 0.0;
  cout << "prediction: " << " with i: " << i / 100.0 << " " 
       << svm_predict(model, test) << endl;
  double *res = new double[2];
  svm_predict_values(model, test, res);
  cout << "value: " << res[0] << endl;
  }
}
/*
void one_class_test2(){
  Dataset dataset("/Users/mauricemulder/workspace/datasets/caltech101/");
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
  //for(int i = 0; i < (int) others.size(); ++i)
    //res[i] = segsvm.classify(&others[i]);
  int total, correct, incorrect;
  for(int i = 0; i < (int) res.size(); i++){
    cout << others[i].get_label() << " " << res[i] 
	 <<  " the values " << segsvm.getValue(&others[i])[0] << endl;
    total++;
    if(res[i] == 1)
      if((int) others[i].get_label())
	correct++;
      else
	incorrect++;
  }
  cout << "total: " << total << endl 
       << "correct: " << correct << endl
       << "incorrect: " << incorrect << endl
       << "precision: " << correct / (double) (incorrect + correct) << endl
       << "recall: " << correct / (double) total << endl;
  cout << "ya done" << endl;
}
*/
