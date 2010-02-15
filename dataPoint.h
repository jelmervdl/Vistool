#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <string>

using namespace std;

class DataPoint{
 private:
  int label;
  string image_url;
  string descriptor_url;
 public:
  DataPoint(size_t lab, string url);
  DataPoint(string url);
  void setDescriptorURL(string url);
  string getImageURL();
  string getDescriptorURL();
  bool hasDescriptor();
  size_t getLabel();
};

#endif
