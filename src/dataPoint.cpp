#include "dataPoint.h"

using std::string;

DataPoint::DataPoint(size_t lab, string fname, string url, string descriptor):
  label(lab),image_url(url),filename(fname),descriptor_url(descriptor){
}


void DataPoint::setDescriptorURL(string url){
  descriptor_url = url;
}

string DataPoint::getImageURL() const {
  return image_url;
}

string DataPoint::getDescriptorURL() const {
  return descriptor_url;
}


size_t DataPoint::getLabel() const {
  return label;
}

string DataPoint::getFileName() const {
  return filename;
}
