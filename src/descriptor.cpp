#include "descriptor.h"

using std::vector;

namespace VisionToolFeatures{

Descriptor::Descriptor(vector<float> vec): vector<float>(vec){
}
Descriptor::Descriptor(int size): vector<float>(size){
}
Descriptor::Descriptor(): vector<float>(){
}

void Descriptor::print() const{
  for(size_t i =0; i < size(); ++i)
    printf("%.2f ", at(i));
}

}
