#include "parameters.h"

XERCES_CPP_NAMESPACE_USE


bool Parameters::instanceFlag = false;
Parameters * Parameters::singleton = NULL;

Parameters::Parameters(){
  readFile("parameters.xml");
}

void Parameters::readFile(char * str){
  XMLPlatformUtils::Initialize();
  cout << "hi" << endl;
  XercesDOMParser* parser = new XercesDOMParser();
  parser->setValidationScheme(XercesDOMParser::Val_Always);
  ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
  parser->setErrorHandler(errHandler);
  parser->parse(str);
  DOMDocument * doc = parser->getDocument();
  DOMElement* elementRoot = doc->getDocumentElement();
  DOMElement* child = elementRoot->getFirstElementChild();
  do{
    cout << "aaak" << endl;
    singleton->save(
		    XMLString::transcode(child->getNodeName()),  
		    atof(XMLString::transcode(child->getTextContent())));
    cout << "aaak" << endl;
    child = child->getNextElementSibling();
    cout << "aaak" << endl;
  }
  while(child != NULL);
  cout << "ho" << endl;
  XMLPlatformUtils::Terminate();
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

void Parameters::save(string str, float f){
  floatParameters[str] = f;
}

bool Parameters::hasHistogram(){
  string reqParams [] = {"hbins", "sbins"};
  return hasParameters(reqParams, 2);
}

bool Parameters::hasParameters(string reqParams[], size_t n){
  for(size_t i = 0; i < n; ++i)
    if(floatParameters.count(reqParams[i]) == 0)
      return false;
  return true;
}

void Parameters::printParameters(){
  for(map<string,float>::iterator it = floatParameters.begin();
      it != floatParameters.end();
      ++it){
    cout << "parameter: " << (*it).first << " " << (*it).second << endl; 
  }
}
