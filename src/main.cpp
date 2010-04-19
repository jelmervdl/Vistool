#include "main.h"

using vito::gui::start;
using vito::optimization::ParameterOptimization;

int main(int argc, char ** argv){

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
      ParameterOptimization opt(&vito::optimization::evaluateSVM);
      opt.optimize();
    }
  }  
  return 0;
}

