#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <vector>

using namespace std;
class Descriptor: public vector<float>{
 private:
  friend Descriptor& operator+(Descriptor& left, const Descriptor& right){
    left.insert(left.end(), right.begin(), right.end());
    return left;
  }
 public:
  Descriptor();
  Descriptor(vector<float> a);
  Descriptor(int size);

};

#endif
