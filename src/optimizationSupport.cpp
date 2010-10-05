#include "optimizationSupport.h"

using std::cout;
using std::endl;

namespace vito{
namespace optimization{

bool ParameterSet::equals(const ParameterSet &other) const{
  if(ints.size() != other.ints.size() || floats.size() != other.floats.size())
    return false;
  for(size_t i = 0; i <  ints.size(); ++i)
    if(ints[i] != other.ints[i])
	return false;
  for(size_t i = 0; i <  floats.size(); ++i)
    if(floats[i] != other.floats[i])
	return false;
  return true;
}

void ParameterSet::print() const{
  cout << "set: ";
  for(size_t i = 0; i < ints.size(); ++i)
    cout << ints[i] << ", " ;
  for(size_t i = 0; i < floats.size(); ++i)
    cout << floats[i] << ", " ;
  cout << endl;
}

}}
