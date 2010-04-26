#include "parameters.h"

using std::collate;
using std::use_facet;
using std::locale;
using std::stringstream;
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

string Parameters::getHashableString(){
  string sift_str = "sift_";
  string hist_str = "histogram_";
  const bool sift_on = intParameters["feature_sift"];
  const bool hist_on = intParameters["feature_histogram"]; 
  stringstream str_str;
  typedef map<string, float>::iterator fl_map_it;
  typedef map<string, int>::iterator i_map_it;
  for(fl_map_it it = floatParameters.begin();
      it != floatParameters.end();
      ++it){
    if( (sift_on && (it->first.find(sift_str) != string::npos) )
	|| 
	(hist_on && (it->first.find(hist_str) != string::npos) ) ){
      str_str << it->first << it->second;
    }
  }
  for(i_map_it it = intParameters.begin(); it != intParameters.end(); ++it)
    if( (sift_on && (it->first.find(sift_str) != string::npos) )
	|| 
	(hist_on && (it->first.find(hist_str) != string::npos) ) ){
      str_str << it->first << it->second;
    }
  return str_str.str();
}


long Parameters::getCurrentHash(){
  string hashable = getHashableString();
  locale loc;
  const collate<char>& coll = use_facet<collate<char> >(loc);
  long hash_ = coll.hash(hashable.data(),hashable.data()+hashable.length());
  return hash_;
}

bool Parameters::compare(string str){
  Parameters other;
  other.readFile((char *)str.c_str());
  typedef map<string, float>::iterator fl_map_it;
  typedef map<string, int>::iterator i_map_it;
  for(fl_map_it it = floatParameters.begin(); it != floatParameters.end(); ++it)
    if(it->second != other.getfParameter(it->first))
      return false;
  for(i_map_it it = intParameters.begin(); it != intParameters.end(); ++it)
    if(it->second != other.getiParameter(it->first))
      return false;
  return true;
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
  DOMElement* floatRoot = (DOMElement *) 
    elementRoot->getElementsByTagName(XMLString::transcode("real"))->item(0);
  DOMElement* child = floatRoot->getFirstElementChild();
  do{
    saveReal(XMLString::transcode(child->getNodeName()),  
		    atof(XMLString::transcode(child->getTextContent())));
    child = child->getNextElementSibling();
  }while(child != NULL);

  // Extract integers
  DOMElement* intRoot = (DOMElement *) 
    elementRoot->getElementsByTagName(XMLString::transcode("integer"))->item(0);
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
  {
    char timeStr[40];
    time_t rawtime;
    struct tm * timeinfo;
    time( &rawtime );
    timeinfo = localtime( &rawtime );
    strftime(timeStr, 40, "%c", timeinfo);
    of << "<!-- " << timeStr  << " -->" << endl;
  }
  of << "<!-- " << str << " -->" << endl << endl;
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
  of.close();
 }
