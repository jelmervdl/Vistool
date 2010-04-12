#include "main.h"

using VisionToolGUI::start;
using parameter_optimization::ParameterOptimization;

float trick(){
  Parameters *parameters = Parameters::getInstance();
  float result = 0;
  float diff = 3.9 - parameters->getfParameter("test");
  result -= diff * diff;
  diff = 4 - parameters->getiParameter("test2");
  result -= diff * diff;
  diff = 11 - parameters->getiParameter("test3");
  result -= diff * diff;
  return result;
}

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
  p->saveXML("hond.xml");
  ParameterOptimization opt(&trick);
  opt.optimize();
  //start(argc, argv);
  return 0;
}

void printLibraries(){
  cout << "hi" << endl;
}
