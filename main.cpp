#include "main.h"

using namespace xercesc;
int main(int argc, char ** argv){
  
  Parameters * param = Parameters::getInstance();
  param->readFile((char *)"parameters.xml");

  vector<Category> cats;
  isDataset("/Users/mauricemulder/workspace/datasets/caltech101", &cats);

  vector<Category> participating;
  participating.push_back(cats.at(0));
  participating.push_back(cats.at(1));
  vector<Sample> samples;
  vector<string> target;
  createTrainAndTestSet(&participating, &samples, &target, 0.8);
  FeatureExtractor *f  = new FeatureExtractor();
  f->createAndSaveDescriptors(&participating);
  delete f;
  cout << "ok: " << DESCRIPTOR_LOCATION << endl;
  */
  //writing
  
  FeatureExtractor * f = new FeatureExtractor();
  
  /*
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

