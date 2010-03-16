#ifndef DESCRIPTOR_WRITER_H
#define DESCRIPTOR_WRITER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

void writeDescriptor(vector<float> * datapoints, string destination);
void readDescriptor(vector<float> * datapoints, string location);
vector<float> readDescriptor(string location);

#endif
