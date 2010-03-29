#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <GLUT/glut.h>
#include <string>

using namespace std;

class DataPoint{
 private:
  int label;
  string image_url;
  string filename;
  string descriptor_url;
 public:
  DataPoint(size_t lab, string filename, string url, string descriptor);
  void setDescriptorURL(string url);
  string getFileName() const;
  string getDescriptorURL() const;
  string getImageURL() const ;
  size_t getLabel() const;
};

#endif
