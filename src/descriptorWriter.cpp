#include "descriptorWriter.h"

using namespace std;

void writeDescriptor(vector<float> * datapoints, string destination){
  size_t elements = datapoints->size();
  ofstream file (destination.c_str(), ios::out | ios::binary); 
  file.write(reinterpret_cast<char *>
	     (&elements),
	     sizeof(elements));
  for(size_t i = 0; i < elements; ++i){
    assert(!isnan(datapoints->at(i)));
    file.write(reinterpret_cast<char *>
	       (&datapoints->at(i)),
	       sizeof(float));
  }
  file.close();
}

void readDescriptor(vector<float> * datapoints, string location){
  size_t elements;

  ifstream file (location.c_str(), ios::in | ios::binary); 
  file.read(reinterpret_cast<char *>
	    (&elements),
	    sizeof(elements));
  datapoints->resize(elements);  
  for(size_t i = 0; i < elements; ++i){
    file.read(reinterpret_cast<char *>
	      (&datapoints->at(i)),
	      sizeof(float));
    assert(!isnan(datapoints->at(i)));
  }
  file.close();
}


vector<float> readDescriptor(string location){
  vector<float> datapoints;
  size_t elements;
  ifstream file (location.c_str(), ios::in | ios::binary); 
  file.read(reinterpret_cast<char *>
	    (&elements),
	    sizeof(elements));
  datapoints.resize(elements);  
  for(size_t i = 0; i < elements; ++i)
    file.read(reinterpret_cast<char *>
	       (&datapoints.at(i)),
	       sizeof(datapoints));
  file.close();
  return datapoints;
}
