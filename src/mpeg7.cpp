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
  Descriptor descriptor = getMPEG7Descriptor(descriptor_path,
						getName());
  cout << "size: " <<  descriptor.size() << endl;
  for(size_t i = 0; i < descriptor.size(); i++){
    descriptor[i] = scale(descriptor[i]);
    cout << descriptor[i] << ",";
  }
  cout << endl;
  descriptor.normalize();
  return descriptor;
}

vector<float> getMPEG7Descriptor(string descriptor_path, string type){
  ifstream in_file_stream(descriptor_path.c_str());
  string line;
  vector<float> ret;
  while(std::getline(in_file_stream, line)){
    if(lineIsOfType(line, type))
      ret = extractNumbers(line);
  }
  return ret;
}

vector<float> extractNumbers(string line){
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

bool lineIsOfType(string line, string type){
  return (int) line.find(type) != -1;
}

string getDescriptorLocation(string loc, bool patches){
  string descriptor_path;
  int last_slash = loc.find_last_of('/');
  int secondlast_slash = loc.find_last_of('/', last_slash - 1);
  {
    string name, category;
    stringstream filepath_stream;
    

    category = loc.substr(secondlast_slash + 1, 
			  last_slash - secondlast_slash - 1);
    name = loc.substr(last_slash + 1, loc.size());
    filepath_stream << "desc/mpeg7/"  << category << "/" << name;
    if(patches)
      filepath_stream << "_patches";
    filepath_stream << ".txt";
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


Matrix<vector<float> > getPatches(string descriptor_path){
  string location = getDescriptorLocation(descriptor_path, true);
  cout << location << endl;
  ifstream infile(location.c_str());
  string line;
  Matrix<vector<float> > matrix (10,10);
  while(std::getline(infile, line)){
    if(lineIsOfType(line, "edgehistogram")){
      vector<float> numbers = extractNumbers(line);
      int x = numbers[0];
      int y = numbers[1];
      matrix.at(x,y) = vector<float>(numbers.begin() + 2, numbers.end());
    }
  }
  //printPatchMatrix(matrix);
  return matrix;
}

void printPatchMatrix(const Matrix<vector <float> > &matrix){
  for(size_t x = 0; x < matrix.get_width(); ++x){
    cout << "x = " << x << " xsize " << matrix.get_width() << endl;
    for(size_t y = 0; y < matrix.get_height(); ++y){
      cout << "x: " << x << " y: " << y << ": ";
      cout << matrix.at(x,y).size() << endl;
      for(size_t i = 0; i < matrix.at(x,y).size(); ++i){
	cout << matrix.at(x,y)[i] << " ";
      }
      cout << endl;
    }
  }
}

vector<vector<float> > getAllPatches(vector<DataPoint> datapoints){
  vector< vector<float> > allpatches;
  for(size_t i = 0; i < datapoints.size(); i++){
  cout << "getting ALLL Patches, of " << datapoints.size()  << " datapoints " 
       << "it's name: " << datapoints[i].get_image_url() << endl;
    const Matrix<vector<float> > matrix = getPatches(datapoints[i].get_image_url());
    for(int x = 0; x < 10; x++)
      for (int y = 0; y < 10; y++)
	allpatches.push_back(matrix.at(x,y));
  } 
  return allpatches;
}



}}}

