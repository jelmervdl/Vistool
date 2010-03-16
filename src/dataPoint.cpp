#include "dataPoint.h"

DataPoint::DataPoint(size_t lab, string fname, string url, string descriptor):
  label(lab),image_url(url),filename(fname),descriptor_url(descriptor){
}


void DataPoint::setDescriptorURL(string url){
  descriptor_url = url;
}

string DataPoint::getImageURL(){
  return image_url;
}

string DataPoint::getDescriptorURL(){
  return descriptor_url;
}


size_t DataPoint::getLabel(){
  return label;
}

string DataPoint::getFileName(){
  return filename;
}
