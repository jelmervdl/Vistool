#include "main.h"
#include "mpeg7.h"
#include "patchExtractor.h"
#include "kmeanshistogram.h"
 
using std::sprintf;
using namespace vito;
using namespace vito::features;
using namespace vito::gui;
using namespace vito::optimization;
using namespace vito::classification;
using namespace std;

void testMPEG7(){
  Dataset dataset("/Users/mauricemulder/workspace/datasets/caltech101/");
  //dataset.enableCategory("accordion");
  dataset.enableCategory("accordion");
  //dataset.enableCategory("emu");
  dataset.enableCategory("buddha");


  //MyImage my_image = MyImage( "../datasets/caltech101/accordion/image_0001.jpg");
  vector<DataPoint> dps = dataset.enabledPoints();
  vector<DataPoint> train, test;
  
  KMeansClusterHistogram<Histogram> aap(&dps);
  MyImage im(dps[0].get_image_url());
  vector<float> hond = aap.extract(&im);



  /*
  DataPoint dp1 = DataPoint(0,
			    "image_0002.jpg",
			    "../datasets/caltech101/emu/image_0002.jpg", 
			    "emu");
  DataPoint dp2 = DataPoint(0,
			    "image_0001.jpg",
			    "../datasets/caltech101/emu/image_0001.jpg", 
			    "emu");
  dps.push_back(dp1);
  dps.push_back(dp2);
  
  //mpeg7::getPatches("../datasets/caltech101/accordion/image_0001.jpg");
  //vector<vector<float> > patches = mpeg7::getAllPatches(dps);
  clustering::PatchExtractor pa;
  vector<vector<float> > patches = pa.getPatches(&dps, Histogram::getInstance());
  clustering::KMeansClustering clustering;
  vector<vector<float> > centers = clustering.cluster(patches);
  vector<int>  classification = clustering.classify_per_patch(centers, patches);
  vector<Magick::Color> colors;
  colors.push_back(Magick::Color("black"));
  colors.push_back(Magick::Color("green"));
  colors.push_back(Magick::Color("yellow"));
  colors.push_back(Magick::Color("red"));
  colors.push_back(Magick::Color("purple"));
  colors.push_back(Magick::Color("blue"));
  colors.push_back(Magick::Color("brown"));
  colors.push_back(Magick::Color("pink"));
  colors.push_back(Magick::Color("gray"));

  clustering.writeClusters(centers);
  vector<vector<float> > cools = clustering.readClusters();

  for(size_t p = 0; p < cools.size(); p++){
    cout << "patch " << p << " has "
	 << cools[p].size() << " items" << endl;
    for(size_t v = 0; v < cools[p].size(); v++)
      cout << cools[p][v] << " ";
    cout << endl;
  }

  for(size_t i = 0; i < dps.size(); i++){
    MyImage image (dps[i].get_image_url());
    Magick::Image mag = *image.getMagickImage();
    for(int x = 0; x < 10; x++){
      for(int y = 0; y < 10; y++){
	const int index = 100 * i + 10 * x + y;
	stringstream a;
	a << classification[index] << "_" << index << "bla.jpg";
	//image.save_sub_image(x, 10, y, 10, a.str());
	int width = mag.columns();
	int height = mag.rows();
	int left = (x / (float) 10) * width;
	int right = ((1 + x) / (float) 10) * width;
	int up = (y / (float) 10) * height;
	int down = ((1 + y) / (float) 10) * height;
	Magick::Color color;
	color.alpha(10.0);
	mag.fillColor(color);
	mag.strokeColor("red");
	mag.draw(Magick::DrawableRectangle(left, up, right, down));
	stringstream b;
	b << classification[index];
	mag.fillColor(colors[classification[index] % colors.size()]);
	mag.strokeColor(color);

	int tleft = left + 10;
	int tup = up + 10;
	if(tleft > width)
	  tleft = left;
	if(tup > height)
	  tup = up;
	Magick::DrawableText text(tleft, tup, b.str());
	mag.draw(text);
      }
    }
    stringstream out;
    out << "bla_" << i << ".jpg";
    mag.write(out.str());
  
  }
  */
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
  Parameters *p = Parameters::getInstance();
  p->readFile((char *) "parameters.xml");
  //testMPEG7();
  vector<DataPoint> dps;
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
      ParameterOptimization opt(&vito::optimization::evaluateOneClassSVM);
      opt.optimize();
    }
  }  
  return 0;
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

