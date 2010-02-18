#include "main.h"
   
using namespace xercesc;
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
  //  start(argc, argv);

  Dataset dset ("/Users/mauricemulder/workspace/datasets/caltech101/");
  dset.enableCategory("airplanes");
  //  dset.enableCategory("accordion");

  FeatureExtractor * f = FeatureExtractor::getInstance();
  NNClassifier n;
  vector<DataPoint> train, test;
  dset.randomSplit(&train, &test, 0.7);
  f->saveDescriptorsToFile(&dset);
  n.train(train);

  /*
  Parameters * param = Parameters::getInstance();
  param->readFile((char *)"parameters.xml");
  Dataset dset ("/Users/mauricemulder/workspace/datasets/caltech101/");
  dset.enableCategory("airplanes");
  dset.enableCategory("accordion");
  dset.print();

  Image image("/Users/mauricemulder/workspace/datasets/caltech101/BACKGROUND_Google/image_0005.jpg");
  Blob blob;
  image.magick("BGR");
  image.write(&blob);
  cout << "image's depth is: " << image.depth() << endl;
  Mat orig, hsv; 
  orig = Mat(image.size().height(),
	     image.size().width(), 
	     CV_8UC3, 
	    (void *) blob.data());
  cvtColor(orig, hsv, CV_BGR2HSV);
  vector<float> a = f->extractHistogram(&hsv);
  free(f);
  free(param);
  */
    
}

void printLibraries(){
  printf("Using Library: %s %d\n", "boost", 1);
  printf("Using Library: %s %d\n", "glui", 1);
  printf("Using Library: %s %d\n", "glut", 1);
  printf("Using Library: %s %d\n", "opengl", 1);
  printf("Using Library: %s %d\n", "magick++", 1);
  printf("Using Library: %s %d\n", "opencv", 1);  
}

