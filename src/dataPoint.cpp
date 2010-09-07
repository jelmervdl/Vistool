#include "dataPoint.h"


using std::string;
using std::cout;
using std::endl;

namespace vito{

DataPoint::DataPoint(size_t lab, 
		     string fname, string url,
		     string cat):
  label(lab),image_url(url),file_name(fname),
  cat_name(cat){
}

string DataPoint::get_image_url() const {
  return image_url;
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

LabelCollection DataPointCollection::getLabels(){
  LabelCollection labels;
  for(DataPointCollection::iterator it = begin();
      it != end();
      ++it)
    labels.push_back(it->get_label());
  return labels;
}

void DataPointCollection::print(){
  cout << "collection has: " << size() << " items: " << endl;
  for(DataPointCollection::iterator it = begin(); it != end(); ++it)
    cout << "  " << "type: " << it->get_label() << " "
	 << it->get_file_name() << endl;
}

}
