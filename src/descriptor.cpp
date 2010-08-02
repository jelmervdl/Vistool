#include "descriptor.h"

using std::vector;

namespace vito{

void Descriptor::normalize(){
  const float min = *std::min_element(begin(), end());
  const float max = *std::max_element(begin(), end());
  const float multiplier = 1 / (max - min);
  for(Descriptor::iterator it = begin(); it != end(); ++it)
    *it = (*it - min) * multiplier;
}

void Descriptor::print() const{
  for(size_t i =0; i < size(); ++i)
    printf("%.5f ", at(i));
}

int Example::get_label() const{
  return label;
}
void Example::set_label(const int l){
  label = l;
}



}
