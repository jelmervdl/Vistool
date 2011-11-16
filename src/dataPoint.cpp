#include "dataPoint.h"
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

using std::string;
using std::cout;
using std::endl;

namespace vito{

DataPoint::DataPoint(size_t lab, string fname, string url, string cat)
:
  label(lab),
  image_url(url),
  file_name(fname),
  cat_name(cat)
{
  //
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
DataPointCollection::DataPointCollection(std::vector<DataPoint> vec)
: 
  std::vector<DataPoint>(vec)
{
  //
}

LabelCollection DataPointCollection::getLabels()
{
  LabelCollection labels;
  for(DataPointCollection::iterator it = begin();
      it != end();
      ++it)
    labels.push_back(it->get_label());
  return labels;
}

void DataPointCollection::print()
{
  cout << "collection has: " << size() << " items: " << endl;
  for(DataPointCollection::iterator it = begin(); it != end(); ++it)
    cout << "  " << "type: " << it->get_label() << " "
	 << it->get_file_name() << endl;
}

DataPointCollection DataPointCollection::getRandomSubSet(size_t subset_size) const
{
  if (subset_size > size())
    throw std::out_of_range("asked random subset cannot be larger than original set");
  
  DataPointCollection copy;
  copy.reserve(subset_size);
  
  for (size_t i = 0; i < subset_size; ++i)
    copy.push_back(at(rand() % size()));

  return copy;
} 

}
