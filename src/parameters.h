#ifndef PARAMETERS_H
#define PARAMETERS_H

#define NO_PARAMETERS 100

#include "singleton.h"
#include <iostream>
#include <map>
#include <string>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

class Parameters:public Singleton <Parameters>{
  friend class Singleton<Parameters>;
  friend class ParameterPanel;
 protected:
  Parameters();
 private:
  std::map<std::string, float> floatParameters;
  std::map<std::string, int> intParameters;
  std::string file;
 public:
  void readFile(char * str);
  std::string getFile();
  void saveReal(std::string str, float f);
  void saveInteger(std::string str, int f);
  float getfParameter(std::string str);
  int  getiParameter(std::string str);
  ~Parameters();
  bool hasHistogram();
  bool hasParameters(std::string * reqParams, size_t n);
  void printParameters();
};

#endif PARAMETERS_H
