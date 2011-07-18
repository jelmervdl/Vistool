#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <iostream>
#include <vector>
#include <string>
#include "labels.h"

/* Contains all relevant information regarding a single
DataPoint. This include the file names of it's original image and the
descriptor that describes it. */

namespace vito{

class DataPoint{
 public:
  DataPoint(size_t      lab, 
	    std::string file_name, 
	    std::string url, 
	    std::string cat);

  std::string get_file_name() const;
  std::string get_cat_name() const;
  std::string get_image_url() const ;
  size_t      get_label() const;
 private:
  int         label;
  std::string image_url;
  std::string file_name;
  std::string cat_name; // category name
};


class DataPointCollection : public std::vector<DataPoint> {
public:
  DataPointCollection(){};
  DataPointCollection(std::vector<DataPoint> vec);
  // create a labelcollection from the labels of the datapoints
  LabelCollection getLabels();
  void print();
};

}

#endif
