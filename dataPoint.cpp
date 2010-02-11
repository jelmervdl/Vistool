#include "dataPoint.h"

DataPoint::DataPoint(size_t lab, string url):
  label(lab),image_url(url){
}

DataPoint::DataPoint(string url):
  label(-1), image_url(url){
}




string DataPoint::getImageURL(){
  return image_url;
}

string DataPoint::getDescriptorURL(){
  return descriptor_url;
}

bool DataPoint::hasDescriptor(){
  return true;
  //TODO implement this stub
}
size_t DataPoint::getLabel(){
  return label;
}
