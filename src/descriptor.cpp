#include "descriptor.h"

using std::vector;

namespace vito{

Descriptor::Descriptor(vector<float> vec): vector<float>(vec){
}
Descriptor::Descriptor(int size): vector<float>(size){
}
Descriptor::Descriptor(): vector<float>(){
}

void Descriptor::print() const{
  for(size_t i =0; i < size(); ++i)
    printf("%.5f ", at(i));
}

int Example::get_label(){
  return label;
}

void Example::Example(int lab) : label(lab){
}

}
