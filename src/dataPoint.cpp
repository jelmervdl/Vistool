#include "dataPoint.h"


using std::string;

namespace vito{

DataPoint::DataPoint(size_t lab, 
		     string fname, string url,
		     string descriptor, string cat):
  label(lab),image_url(url),file_name(fname),
  descriptor_url(descriptor), cat_name(cat){
}

void DataPoint::setDescriptorURL(string url){
  descriptor_url = url;
}

string DataPoint::get_image_url() const {
  return image_url;
}

string DataPoint::get_descriptor_url() const {
  return descriptor_url;
}

size_t DataPoint::get_label() const {
  return label;
}

string DataPoint::get_file_name() const {
  return file_name;
}

string DataPoint::get_cat_name() const{
  return cat_name;
}

}
