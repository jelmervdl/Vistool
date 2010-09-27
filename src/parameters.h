/* Stores all experiment and gui parameters, including feature
   extraction, classification and display. Parameters is static but
   can be changed during an experiment.*/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#define NO_PARAMETERS 100

#include "singleton.h"
#include "multiton.h"
#include "parameterOptimization.h"
#include <locale>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

namespace vito{
namespace optimization{
class ParameterOptimization;
}
namespace gui{
class FeatureSelectionWindow;
}
}

class Parameters : public Multiton<Parameters>{
  friend class Singleton<Parameters>;
  friend class Multiton<Parameters>;
  friend class ParameterPanel;
  friend class vito::optimization::ParameterOptimization;
  friend class vito::gui::FeatureSelectionWindow;
 protected:
  Parameters();
 private:
  std::map<std::string, float> floatParameters;
  std::map<std::string, int> intParameters;
  std::string file;

 public:

  void        clear();

  void        appointFeature(std::string str);
  void        turnOffAllFeatures();
  // constructor
             ~Parameters();

  // get the last xml file from which parameters came 
  std::string getFile();

  // Read in a parameter file, can be done incrementally
  void        readFile(std::string str);

  // save a new real parameter under a string name
  void        saveReal(std::string str, 
		       float f);

  // save a new integer parameter under a string name 
  void        saveInteger(std::string str, int f);

  // get the value of a float parameter
  float       getfParameter(std::string str) ;

  // get the value of a integer parameter
  int         getiParameter(std::string str);

  void        saveXML(std::string str);

  long        getCurrentHash();
  std::string getHashableString();

  bool        compare(std::string str);

  bool        hasParameters(std::string * reqParams, size_t n);

  void        printParameters();

  void        requireOnlySift();
};

#endif PARAMETERS_H
