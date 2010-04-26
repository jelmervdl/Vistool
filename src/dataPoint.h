#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <string>

/* Contains all relevant information regarding a single
DataPoints. This include the file names of it's original image and the
descriptor that describes it. */

namespace vito{

class DataPoint{
 private:
  int         label;
  std::string image_url;
  std::string file_name;
  std::string descriptor_url;
  std::string cat_name;

 public:
  DataPoint(size_t      lab, 
	    std::string file_name, 
	    std::string url, 
	    std::string descriptor,
	    std::string cat);

  void        setDescriptorURL(std::string url);
  std::string get_file_name() const;
  std::string get_cat_name() const;
  std::string get_descriptor_url() const;
  std::string get_image_url() const ;
  size_t      get_label() const;
};

}

#endif
