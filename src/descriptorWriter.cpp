#include "descriptorWriter.h"
#include "cache.hpp"
#include "boost/filesystem.hpp"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <math.h>

using namespace std;

namespace vito{
namespace write{

Cache<vector<float> > descriptor_cache;

const bool use_disk = false;

void writeDescriptor(vector<float> * datapoints, string destination)
{
  if (use_disk)
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
  }

  descriptor_cache.add(destination, *datapoints);
}

void readDescriptor(vector<float> * datapoints, string location)
{
  if (descriptor_cache.contains(location))
  {
    *datapoints = descriptor_cache.get(location);
    return;
  }
  
  if (use_disk)
  {
    size_t elements;
    ifstream file(location.c_str(), ios::in | ios::binary); 
    file.read(reinterpret_cast<char *>(&elements), sizeof(elements));

    datapoints->resize(elements);
    for (size_t i = 0; i < elements; ++i)
    {
      file.read(reinterpret_cast<char *>(&datapoints->at(i)), sizeof(float));
      assert(!isnan(datapoints->at(i)));
    }

    file.close();
  }
  else
  {
    throw runtime_error(string("Descriptor ") + location + " not in cache");
  }
}


vector<float> readDescriptor(string location)
{
  if (descriptor_cache.contains(location))
    return descriptor_cache.get(location);
  
  if (use_disk)
  {
    vector<float> datapoints;
    size_t elements;
    ifstream file (location.c_str(), ios::in | ios::binary); 
    file.read(reinterpret_cast<char *>(&elements), sizeof(elements));

    datapoints.resize(elements);  
    for (size_t i = 0; i < elements; ++i)
    {
      file.read(reinterpret_cast<char *>(&datapoints.at(i)), sizeof(datapoints));
      assert(!isnan(datapoints.at(i)));
    }
    
    file.close();
    return datapoints;
  }
  else
  {
    throw runtime_error(string("Descriptor ") + location + " not in cache");
  }
}

bool descriptorExists(string const &location)
{
  return descriptor_cache.contains(location)
      || use_disk && boost::filesystem::exists(boost::filesystem::path(location));
}

}}
