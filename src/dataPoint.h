#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <GLUT/glut.h>
#include <string>

class DataPoint{
 private:
  int label;
  std::string image_url;
  std::string filename;
  std::string descriptor_url;
 public:
  DataPoint(size_t lab, std::string filename, std::string url, std::string descriptor);
  void setDescriptorURL(std::string url);
  std::string getFileName() const;
  std::string getDescriptorURL() const;
  std::string getImageURL() const ;
  size_t getLabel() const;
};

#endif
