#ifndef PARAMETERS_H
#define PARAMETERS_H

#define NO_PARAMETERS 100

#include <iostream>
#include <map>
#include <string>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace std;

class Parameters{
 private:
  static bool instanceFlag;
  static Parameters * singleton; 
  map<string, float> floatParameters;
  map<string, int> intParameters;
  Parameters();
 public:
  void readFile(char * str);
  static Parameters * getInstance();
  void saveReal(string str, float f);
  void saveInteger(string str, int f);
  float getfParameter(string str);
  int  getiParameter(string str);
  ~Parameters();
  bool hasHistogram();
  bool hasParameters(string * reqParams, size_t n);
  void printParameters();
};

#endif PARAMETERS_H
