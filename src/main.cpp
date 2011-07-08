#include "main.h"

#include "facedetect.h"

using std::sprintf;
using namespace vito;
using namespace vito::features;
using namespace vito::gui;
using namespace vito::optimization;
using namespace vito::classification;
using namespace std;


void testFaceRec(){
  string cascadeName =
    "data/haarcascades/haarcascade_frontalface_alt.xml";
  string nestedCascadeName =
    "data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
  cv::Mat im = 
    cv::imread("../datasets/caltech101/BACKGROUND_Google/image_0197.jpg", 1);
  cv::CascadeClassifier cascade, nestedCascade;
  double scale = 1;
  if( !nestedCascade.load( nestedCascadeName ) )
    cerr << "WARNING: Could not load classifier cascade for nested objects" 
	 << endl;
  if( !cascade.load( cascadeName ) ) {
      cerr << "ERROR: Could not load classifier cascade" << endl;
      cerr << "Usage: facedetect [--cascade=\"<cascade_path>\"]\n"
            "   [--nested-cascade[=\"nested_cascade_path\"]]\n"
            "   [--scale[=<image scale>\n"
	"   [filename|camera_index]\n" ;
      return;
  }
  cout << vito::features::detect(im, cascade, nestedCascade, scale);
}

void testClassifierStack(){
  Dataset dataset(string(DATASET_LOCATION) + "caltech101/");
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
    cout << "getting examples to train the stack " <<endl;
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
  Dataset::setPrefferedDataset("abdullah2010");
  // get out the options
  for(int i = 1; i < argc; i++){
    if(argv[i][0] == '-' && argc > (i + 1) ){
      string option_name = string(argv[i]).substr(1);
      string value = argv[i + 1];
      cout << option_name << " : " << value << endl;
      i++;
      if(option_name == "d"){
	Dataset::setPrefferedDataset(value);
      }
      if(option_name == "p"){
	p->readFile(value);
      }if(option_name == "c" || option_name == "C"){
	int par = Parameters::getUnique();
	Parameters::push(par);
	Parameters::getInstance()->readFile(value + ".xml");
	vector<features::Feature*> actives = features::getActiveFeatures();
	assert(actives.size() == 1);
	clustering::TrueClusterHistogram *c_feature =
	  new clustering::TrueClusterHistogram(value, actives[0]);
	features::ClusterFeatureExtractor::getInstance()->
	  addClusterFeature(c_feature);
	Parameters::pop();
	if(option_name == "C"){
	  Parameters::getInstance()->
	    appointFeature(c_feature->getParameterName());
	  //Dataset ds = experiment::abdullah2010();
	  //c_feature->drawRandomPatches(ds.enabledPoints());
	}
      }
      if(option_name == "naive"){
	cout << "creating naive feature..." << endl;
	vector<string> files = getFiles(value, ".xml");
	SetupFeature  naiveStack;
	cout << "adding setup files: ";
	typedef vector<string>::iterator strit;
	for(strit i = files.begin(); i != files.end(); ++i){
	  naiveStack.push_back(Setup(*i));
	  cout << " " << *i << " ";
	}
	cout << endl;
	Parameters::getInstance()->appointFeature(naiveStack.getParameterName());
	NaiveStackFeatures::getInstance()->push_back(naiveStack);
      }
      if(option_name == "svmstack"){
	cout << "creating naive feature..." << endl;
	vector<string> files = getFiles(value, ".xml");
	features::SVMStack svmStack;
	cout << "adding setup files: ";
	typedef vector<string>::iterator strit;
	for(strit i = files.begin(); i != files.end(); ++i){
	  svmStack.push_back(SVMActivationSetup(*i));
	  cout << " " << *i << " ";
	}
	cout << endl;
	Parameters::getInstance()->appointFeature(svmStack.getParameterName());
	SVMStackFeatures::getInstance()->push_back(svmStack);
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
  if(*arg == "thread_test"){
    test_threads();
    return 0;
  }
  if(*arg == "face"){
    testFaceRec();
    return 0;
  }
  if(*arg == "test"){
    testing::testAll();
    return 0;
  }
  if(*arg == "gui"){
    //stack_function();
    //stack_svm();
    start(1,argv);
    return 0;
  }
  if(*arg == "optimize"){
    //stack_function();
    cout << "optimizing..." << endl;
    ParameterOptimization opt(&vito::optimization::evaluateSVMAbdullah);
    arg++;
    if(arg == end){
      opt.optimize_full_grid();
      experiment::performExperiment("svm",
				    Dataset::getPrefferedDatasetName(),
				    100);
    }else {
      string original = *arg;
      arg++;
      if(arg == end){
	string target = original;
	cout << "optimizing current setup (no original) with target "
	     << target << endl;
	opt.optimize_full_grid("",target);
	experiment::performExperiment("svm",
				      Dataset::getPrefferedDatasetName(),
				    100);	
      }
      if(arg != end){
	string target = *arg;
	cout << "optimizing " << original << " to target: " << target << endl;
	arg++;
	if(arg == end){
	  opt.optimize_full_grid(original, target);
	  experiment::performExperiment("svm",
					Dataset::getPrefferedDatasetName(),
					100);
	}
      }
    }
    return 0;
  }
  if(*arg == "fulloptimize"){
    //stack_svm();
    ParameterOptimization opt(&vito::optimization::evaluateSVMAbdullah);
    opt.optimize_full_grid();
    return 0;
  }
  if(*arg == "recall"){
    experiment::recallExperiment();
    return 0;
  }
  if(*arg == "stack"){
    arg++;
    if(arg == end){
      stack_function();
      return 0;
    }
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
      //stack_function();
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
    int kdps = atoi(arg->c_str());
    arg++;
    if(arg == end){
      experiment::performExperiment(type, dataset, reps, kdps);	  
      return 0;
    }
  }if(*arg == "cluster"){
    arg++;
    if(arg == end){
      cout << "no filename and dataset supplied" << endl;
      return 1;
    }else{
      cout << "clustering dataset: " << *arg << endl;
      string dataset = *arg;
      arg++;
      if(arg == end ){
	cout << "no filename supplied" <<endl;
	return 1;
      }else{
	cout << "saving to: " << *arg << endl;
	experiment::cluster(dataset, *arg);
	return 0;
      }
    }

  }if(*arg == "help"){
    arg++;
    if(arg == end){
      cout << "   help" << endl << "   experiment" << endl 
	   << "   gui" << endl << "   optimize" << endl << "   cluster" << endl;
      return 0;
    }
  }if(*arg == "studentt"){
    arg++;
    if(arg == end){
      studentTTest::perform();				   
      return 0;
    }
  }
  if(arg != end){
    cout << end - arg << " to go " << endl;
    cout << "following arguments were ignored:" << endl;
      while(arg != end){
	arg++;
	cout << *arg << endl;
      }
  }

  cout << "type help for a list of commands" << endl;
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

class Aap{
  int foo_;
  int bar_;
public:
  Aap() : foo_(0) , bar_(0){}

  void foo(){
    foo_ = 0;
    for(int i = 1; i < 10000; ++i){
      foo_ += i;
    }
  }

  void bar(){
    bar_ = 1;
    for(int i = 1; i < 10000; ++i){
      bar_ += 2 * i;
    }
  }

    void print(){
      cout << "foo: " << foo_ << endl;
      cout << "bar: " << bar_ << endl;
    }
};

void test_threads(){
  Aap aap;
  boost::thread thread_1( &Aap::foo, &aap);
  aap.print();
  boost::thread thread_2( &Aap::bar, &aap);
  aap.print();
  aap.print();
  aap.print();
  thread_2.join();
  aap.print();
  aap.print();
  aap.print();
  thread_1.join();
  aap.print();
}

void stack_function(){
  /*
  SVMClassifier svm;
  SetupFeature setups;
  setups.push_back(Setup("experiments/basic_sift_L0.5.xml"));
  setups.push_back(Setup("experiments/basic_sift_L2.xml"));
  Dataset dataset ("../datasets/caltech101/");
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
  SetupFeature setup_feature;

  //setup_feature.push_back(Setup("experiments/basic_sift_L2.xml"));
  setup_feature.push_back(Setup("experiments/sift_L1_4oris.xml"));
  setup_feature.push_back(Setup("experiments/sift_L1_4oris_phase_shift.xml"));
  Parameters::getInstance()->appointFeature(setup_feature.getParameterName());
  NaiveStackFeatures::getInstance()->push_back(setup_feature);


  // gets: mean: 0.867692 +- 0.0235648
  //setup_feature.push_back(Setup("experiments/basic_sift_L1.xml"));
  //setup_feature.push_back(Setup("experiments/basic_sift_L0.xml"));
  //Parameters::getInstance()->saveReal("svm_gamma", 0.007562);
  //Parameters::getInstance()->saveReal("svm_C", 2.405164);
  //
  //FeatureSetup b((Classifier *) &svm, "experiments/basic_sift_L2.xml");
}

void stack_svm(){
  Dataset abdul = experiment::abdullah2010();
  vector<Dataset> sets = abdul.split();
  DataPointCollection train = sets[0].enabledPoints();
  DataPointCollection test = sets[1].enabledPoints();
  features::SVMStack stack;
  {
    using features::SVMActivationSetup;
    stack.push_back(SVMActivationSetup("experiments/basic_sift_L0.xml"));
    stack.push_back(SVMActivationSetup("experiments/basic_sift_L1.xml"));
    stack.push_back(SVMActivationSetup("experiments/basic_sift_L2.xml"));
  }
  Parameters::getInstance()->appointFeature(stack.getParameterName());
  SVMStackFeatures::getInstance()->push_back(stack);
  //classification::SVMClassifier svm;
  //features::FeatureExtractor *fe = FeatureExtractor::getInstance();
  //svm.train(fe->getExamples(train));
  //LabelCollection labels = svm.classify(fe->getDescriptors(test));
  //evaluation::Evaluation evaluation(test, labels);
  //evaluation.print();
}

vector<string> getFiles(string root, string extension){
  cout << root << endl;
  using namespace boost::filesystem;
  vector<string> files;
  path stack_path = system_complete(root);
  if(is_directory(stack_path)){
    directory_iterator dir_end;
    for( directory_iterator i(stack_path); i != dir_end; ++i){
      cout << "a file: " << i->path() << endl;
      if(((string) i->path().extension()) == extension)
	files.push_back((string) i->path().file_string());      
    }
  }
  return files;
}
