#ifndef DESCRIPTOR_WRITER_H
#define DESCRIPTOR_WRITER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <math.h>

namespace vito{
namespace write{

void writeDescriptor(std::vector<float> * datapoints, std::string destination);
void readDescriptor(std::vector<float> * datapoints, std::string location);
std::vector<float> readDescriptor(std::string location);

}}

#endif
