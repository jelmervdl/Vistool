/* Stores all experiment and gui parameters, including feature
   extraction, classification and display. Parameters is static but
   can be changed during an experiment.*/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#define NO_PARAMETERS 100

#include <locale>
#include <sstream>
#include <stdio.h>
#include "singleton.h"
#include "multiton.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "parameterOptimization.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

namespace vito{
  namespace optimization{
  class ParameterOptimization;
}}

class Parameters : public Singleton<Parameters>{
  friend class Singleton<Parameters>;
  friend class ParameterPanel;
  friend class vito::optimization::ParameterOptimization;
 protected:
  Parameters();
 private:
  std::map<std::string, float> floatParameters;
  std::map<std::string, int> intParameters;
  std::string file;


 public:
             ~Parameters();

  void        readFile(char * str);
  std::string getFile();

  void        saveReal(std::string str, float f);
  void        saveInteger(std::string str, int f);

  float       getfParameter(std::string str) ;
  int         getiParameter(std::string str);

  void        saveXML(std::string str);

  long        getCurrentHash();
  std::string getHashableString();

  bool        compare(std::string str);

  bool        hasParameters(std::string * reqParams, size_t n);

  void        printParameters();
};

#endif PARAMETERS_H
