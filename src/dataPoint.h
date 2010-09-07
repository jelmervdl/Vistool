#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <iostream>
#include <vector>
#include <string>
#include "labels.h"

/* Contains all relevant information regarding a single
DataPoints. This include the file names of it's original image and the
descriptor that describes it. */

namespace vito{

class DataPoint{
 private:
  int         label;
  std::string image_url;
  std::string file_name;
  std::string cat_name;

 public:
  DataPoint(size_t      lab, 
	    std::string file_name, 
	    std::string url, 
	    std::string cat);

  std::string get_file_name() const;
  std::string get_cat_name() const;
  std::string get_image_url() const ;
  size_t      get_label() const;
};

class DataPointCollection : public std::vector<DataPoint> {
public:
  LabelCollection getLabels();
  void print();
};

}

#endif
