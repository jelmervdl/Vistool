#ifndef DESCRIPTOR_WRITER_H
#define DESCRIPTOR_WRITER_H

#include <string>
#include <vector>

namespace vito{
namespace write{

// read an write descriptor binary files 

void               writeDescriptor(std::vector<float> * datapoints, std::string destination);
void               readDescriptor(std::vector<float> * datapoints, std::string location);
std::vector<float> readDescriptor(std::string location);
bool 			   descriptorExists(std::string const &location);

}}

#endif

