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
  start(argc, argv);

  Dataset dset ("/Users/mauricemulder/workspace/datasets/caltech101/");
  dset.enableCategory("airplanes");
  dset.enableCategory("accordion");

  FeatureExtractor * f = FeatureExtractor::getInstance();
  NNClassifier n(1);
  vector<DataPoint> train, test;
  dset.rSplit(&train, &test, 0.7);
  f->saveDescriptorsToFile(&dset);
  n.train(&train);
  vector<int> rob = n.classify(&test);
  for(vector<int>::iterator it = rob.begin(); it != rob.end(); ++it)
      cout << *it;
  cout << endl;    
}

void printLibraries(){
  printf("Using Library: %s %d\n", "boost", 1);
  printf("Using Library: %s %d\n", "glui", 1);
  printf("Using Library: %s %d\n", "glut", 1);
  printf("Using Library: %s %d\n", "opengl", 1);
  printf("Using Library: %s %d\n", "magick++", 1);
  printf("Using Library: %s %d\n", "opencv", 1);  
}

