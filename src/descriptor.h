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
  Descriptor();
  Descriptor(std::vector<float> a);
  Descriptor(int size);
  void print() const;

};

}
#endif
