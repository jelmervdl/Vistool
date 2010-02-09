#include "parameters.h"

XERCES_CPP_NAMESPACE_USE


bool Parameters::instanceFlag = false;
Parameters * Parameters::singleton = NULL;

Parameters::Parameters(){
}

Parameters::~Parameters(){
  instanceFlag = false;
}

Parameters * Parameters::getInstance(){
  if(!instanceFlag){
    singleton = new Parameters();
    instanceFlag = true;
  }
  return singleton;
}

void Parameters::saveReal(string str, float f){
  floatParameters[str] = f;
}

void Parameters::saveInteger(string str, int f){
  intParameters[str] = f;
}

bool Parameters::hasHistogram(){
  string reqParams [] = {"hbins", "sbins"};
  return hasParameters(reqParams, 2);
}

bool Parameters::hasParameters(string reqParams[], size_t n){
  for(size_t i = 0; i < n; ++i)
    if(floatParameters.count(reqParams[i]) == 0
       && intParameters.count(reqParams[i]) == 0)
      return false;
  return true;
}

void Parameters::printParameters(){
  cout << "Real parameters" << endl;
  for(map<string,float>::iterator it = floatParameters.begin();
      it != floatParameters.end();
      ++it){
    cout << "parameter: " << (*it).first << " " << (*it).second << endl; 
  }
  cout << "Integer parameters" << endl;
  for(map<string,int>::iterator it = intParameters.begin();
      it != intParameters.end();
      ++it){
    cout << "parameter: " << (*it).first << " " << (*it).second << endl; 
  }
}

float Parameters::getfParameter(string str){
  return floatParameters[str];
}
int  Parameters::getiParameter(string str){
  return intParameters[str];
}

void Parameters::readFile(char * str){
  XMLPlatformUtils::Initialize();
  XercesDOMParser* parser = new XercesDOMParser();
  parser->setValidationScheme(XercesDOMParser::Val_Always);
  ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
  parser->setErrorHandler(errHandler);
  parser->parse(str);
  DOMDocument * doc = parser->getDocument();
  DOMElement* elementRoot = doc->getDocumentElement();

  // Extract floats
  DOMElement* floatRoot = (DOMElement *) elementRoot->
    getElementsByTagName(XMLString::transcode("real"))->item(0);
  DOMElement* child = floatRoot->getFirstElementChild();
  do{
    singleton->saveReal(XMLString::transcode(child->getNodeName()),  
		    atof(XMLString::transcode(child->getTextContent())));
    child = child->getNextElementSibling();
  }while(child != NULL);

  // Extract integers
  DOMElement* intRoot = (DOMElement *) elementRoot->getElementsByTagName(XMLString::transcode("integer"))->item(0);
  child = intRoot->getFirstElementChild();
  do{
    singleton->saveInteger(
		    XMLString::transcode(child->getNodeName()),  
		    atoi(XMLString::transcode(child->getTextContent())));
    child = child->getNextElementSibling();
  }while(child != NULL);

  XMLPlatformUtils::Terminate();
}
