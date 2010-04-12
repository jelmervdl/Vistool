#include "main.h"
#include <map>


using VisionToolGUI::start;
using parameter_optimization::ParameterOptimization;

float trick(){
  return 0.0;
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
  ParameterOptimization opt(&trick);
  //opt.optimize();
  //start(argc, argv);
  return 0;
}

void printLibraries(){
  cout << "hi" << endl;
}
