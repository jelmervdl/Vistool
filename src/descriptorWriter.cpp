#include "descriptorWriter.h"
#include "cache.hpp"

using namespace std;

namespace vito{
namespace write{

Cache<vector<float> > descriptor_cache;

void writeDescriptor(vector<float> * datapoints, string destination)
{
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

  descriptor_cache.add(destination, *datapoints);
}

void readDescriptor(vector<float> * datapoints, string location)
{
  size_t elements;

  if (descriptor_cache.contains(location))
  {
    *datapoints = descriptor_cache.get(location);
    return;
  }

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


vector<float> readDescriptor(string location)
{
  if (descriptor_cache.contains(location))
    return descriptor_cache.get(location);

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

}}
