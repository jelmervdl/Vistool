#include "parameters.h"

using std::string;
using std::map;
using std::cout;
using std::endl;
using std::ofstream;

XERCES_CPP_NAMESPACE_USE

Parameters::Parameters(){
}

Parameters::~Parameters(){
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

string Parameters::getFile(){
  return file;
}

void Parameters::readFile(char * str){
  file = str;
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
    saveReal(XMLString::transcode(child->getNodeName()),  
		    atof(XMLString::transcode(child->getTextContent())));
    child = child->getNextElementSibling();
  }while(child != NULL);

  // Extract integers
  DOMElement* intRoot = (DOMElement *) elementRoot->getElementsByTagName(XMLString::transcode("integer"))->item(0);
  child = intRoot->getFirstElementChild();
  do{
    saveInteger(
		    XMLString::transcode(child->getNodeName()),  
		    atoi(XMLString::transcode(child->getTextContent())));
    child = child->getNextElementSibling();
  }while(child != NULL);

  XMLPlatformUtils::Terminate();
}

void Parameters::saveXML(string str){
  ofstream of(str.c_str());
  of << "<?xml version = \"1.0\" encoding=\'UTF-8\'?>" << endl;
  of << "<parameters>" << endl << endl;
  of << "<integer>" << endl;
  { // write paramters
    typedef map<string,int>::iterator intMapIterator;
    for(intMapIterator map_it = intParameters.begin();
	map_it !=  intParameters.end(); ++ map_it)
      of << "<" << map_it->first << "> " << map_it->second 
	 << " </" << map_it->first << ">" << endl;
  }
  of << "</integer>" << endl << endl;
  of << "<real>" << endl;
  { // write parameters
    typedef map<string,float>::iterator floatMapIterator;
    for(floatMapIterator map_it = floatParameters.begin();
	map_it !=  floatParameters.end(); ++ map_it)
      of << "<" << map_it->first << "> " << map_it->second 
	 << " </" << map_it->first << ">" << endl;
  }

  of << "</real>" << endl << endl;
  of << "</parameters>" << endl;
 }
