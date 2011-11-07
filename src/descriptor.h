#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include "dataPoint.h"
#include <utility>

namespace vito{


/* Descriptor class used to stare image descriptors */
class Descriptor : public std::vector<float>{
 private:
  friend Descriptor& operator+(Descriptor& left, const Descriptor& right){
    left.insert(left.end(), right.begin(), right.end());
    return left;
  }
  int d_label;
 public:
  Descriptor();
  Descriptor(std::vector<float> const &other);
  Descriptor(size_t size);
  void print() const;
  void normalize();
  void normalize(const float min, const float max);
  
  int get_label() const;
  void set_label(int l);

  // returns euclidian distance (for now)
  float distance(const Descriptor &b) const; 

};

class DescriptorCollection : public std::vector<Descriptor> {
public:
  DescriptorCollection();
  DescriptorCollection(DescriptorCollection const &collection);
  DescriptorCollection(size_t size);
  void print();
  std::pair<float,float> normalize();
};


} // namespace vito
#endif
