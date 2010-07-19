#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <vector>

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

};

class Example : public Descriptor{
private:
  int label;
public:
  Example() : Descriptor() {}
  Example(size_t size) : Descriptor(size) {}
  Example(std::vector<float> values) : Descriptor(values) {}
  void set_label(const int i);
  int get_label() const;
};

class ExampleCollection : public std::vector<Example> {
public:
  ExampleCollection() : std::vector<Example>() {}
  ExampleCollection(size_t size) : std::vector<Example>(size){}
};


class DescriptorCollection : public std::vector<Descriptor> {
public:
  DescriptorCollection(const ExampleCollection &collection){
    for(size_t i = 0; i < collection.size(); i++)
      push_back((Descriptor&) collection[i]);
  }
  DescriptorCollection(size_t size) : std::vector<Descriptor> (size) {}
};


}
#endif
