#include "descriptor.h"

using std::vector;

namespace vito{

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
