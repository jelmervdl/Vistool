#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <math.h>
#include <assert.h>
#include "dataPoint.h"
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>

namespace vito{

class Descriptor : public std::vector<float>{
 private:
  friend Descriptor& operator+(Descriptor& left, const Descriptor& right){
    left.insert(left.end(), right.begin(), right.end());
    return left;
  }
 public:
  Descriptor() : std::vector<float>(){}
  Descriptor(std::vector<float> a) : std::vector<float>(a){}
  Descriptor(int size) : std::vector<float>(size){}
  void print() const;
  void normalize();
  void normalize(const float min, const float max);
  float distance(const Descriptor &b) const;

};

class Example : public Descriptor{
private:
  int label;
public:
  Example() : Descriptor() {}
  Example(size_t size) : Descriptor(size) {}
  Example(std::vector<float> values) : Descriptor(values) {}
  Example(std::vector<float> values, int l) : Descriptor(values), label(l){}
  void set_label(const int i);
  int get_label() const;
};


class ExampleCollection : public std::vector<Example> {
public:
  const DataPointCollection dps;
  ExampleCollection() : std::vector<Example>() {}
  ExampleCollection(size_t size) : std::vector<Example>(size){}
  /*ExampleCollection(DataPointCollection dps_) : 
    std::vector<Example>(), dps(dps_) {}
  ExampleCollection(size_t size, DataPointCollection dps_) :
    std::vector<Example>(size), dps(dps_){}
  */
  void print();
};

class DescriptorCollection : public std::vector<Descriptor> {
public:
  DescriptorCollection(){}
  DescriptorCollection(const ExampleCollection &collection){
    for(size_t i = 0; i < collection.size(); i++)
      push_back((Descriptor&) collection[i]);
  }
  DescriptorCollection(size_t size) : std::vector<Descriptor> (size) {}
};


}
#endif
