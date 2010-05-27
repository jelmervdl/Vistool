#include "mpeg7.h"

namespace vito{
namespace features{
namespace mpeg7{

using std::stringstream;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;

using Magick::Image;

using boost::filesystem::path;
using boost::filesystem::exists;

bool MPEG7Feature::isActive(){
  return false;
}

Descriptor MPEG7Feature::extract_(MyImage *image,
				  bool makeVisualRepresentation,
				  Image *representation){
  string descriptor_path =
  getDescriptorLocation(image->getLocation());
  vector<float> descriptor = getMPEG7Descriptor(descriptor_path,
						getName());
  cout << "size: " <<  descriptor.size() << endl;
  return descriptor;
}

vector<float> MPEG7Feature::getMPEG7Descriptor(string descriptor_path, string type){
  ifstream in_file_stream(descriptor_path.c_str());
  string line;
  vector<float> ret;
  while(std::getline(in_file_stream, line)){
    if(lineIsOfType(line, type))
      ret = extractNumbers(line);
  }
  return ret;
}

vector<float> MPEG7Feature::extractNumbers(string line){
  vector<float> ret;
  stringstream ss;
  for(int i = 0; i < (int) line.size(); ++i){
    if(std::isdigit(line[i]) || line[i] == '.' || line[i] == '-')
      ss << line[i];
    else if(ss.str().size() > 0){
         ret.push_back(std::atof(ss.str().c_str()));
      ss.str("");
    }
  }
  return ret;

}

bool MPEG7Feature::lineIsOfType(string line, string type){
  return line.find(type) != -1;
}

string MPEG7Feature::getDescriptorLocation(string loc){
  cout << "hi I'm gonna do " << loc << endl;
  string descriptor_path;
  int last_slash = loc.find_last_of('/');
  int secondlast_slash = loc.find_last_of('/', last_slash - 1);
  {
    string name, category;
    stringstream filepath_stream;
    

    category = loc.substr(secondlast_slash + 1, 
			  last_slash - secondlast_slash - 1);
    name = loc.substr(last_slash + 1, loc.size());
    filepath_stream << "desc/mpeg7/"  << category << "/" << name << ".txt";
    descriptor_path = filepath_stream.str();
  }
  cout << descriptor_path << endl;
  if(!exists(path(descriptor_path))){
    stringstream javacommand;
    string category_root = loc.substr(0, last_slash);
    javacommand << "java "
		<< "-cp " << MPEG7_JAVA_CLASS_LOCATION << " "
		<< "features.MPEG7FeatureExtractor "
		<< category_root;
    cout << javacommand.str() << endl;
    std::system(javacommand.str().c_str());
  } 
  if(!exists(path(descriptor_path))){
    cout << "problem extracting feature!" << endl;
    return "";
  } 
  return descriptor_path;
}

}}}
