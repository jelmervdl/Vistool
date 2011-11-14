#include "descriptor.h"
#include "foreach.h"
#include <algorithm>
#include <map>
#include <cmath>
#include <cassert>

using std::vector;
using std::map;
using std::cout;
using std::endl;


namespace vito{

Descriptor::Descriptor()
:
  std::vector<float>()
{}

Descriptor::Descriptor(std::vector<float> const &other)
:
  std::vector<float>(other)
{}

Descriptor::Descriptor(size_t size)
:
  std::vector<float>(size)
{}

void Descriptor::normalize()
{
  const float min = *std::min_element(begin(), end());
  const float max = *std::max_element(begin(), end());
  normalize(min, max);
}

float Descriptor::distance(const Descriptor &other) const
{
  assert(size() == other.size());
  float total_distance = 0.0;
  Descriptor::const_iterator 
    a = begin(),
    b = other.begin();
  while(a != end()){
    float cdist = *a - *b;
    total_distance += cdist * cdist;
    ++a;
    ++b;
  }
  return sqrt(total_distance);
}

void Descriptor::normalize(const float min, const float max)
{
  float multiplier = 2 / (max - min);
  if((min - max) == 0)
    multiplier = 0.0;
  for(Descriptor::iterator i = begin(); i != end(); ++i){
    *i = -1 + (*i - min) * multiplier;
    if(*i > 1)
      *i = 1;
    if(*i < -1)
      *i = -1; 
  }
}

void Descriptor::print() const
{
  for(size_t i =0; i < size(); ++i)
    cout << at(i) << endl;
}


DescriptorCollection::DescriptorCollection()
:
  std::vector<Descriptor>()
{}

DescriptorCollection::DescriptorCollection(DescriptorCollection const &other)
:
  std::vector<Descriptor>(other)
{}

DescriptorCollection::DescriptorCollection(size_t size)
:
  std::vector<Descriptor>(size)
{}

void DescriptorCollection::print()
{
  map<int,int> label_histogram;
  // make histogram of all labels
  for(DescriptorCollection::iterator it = begin(); 
      it != end();
      ++it)
    label_histogram[it->get_label()]++;
  // print histogram values
  for(map<int,int>::iterator it = label_histogram.begin(); 
      it != label_histogram.end();
      ++it)
    cout << it->first << " has: " << it->second << endl;
}

int Descriptor::get_label() const
{
  return d_label;
}
void Descriptor::set_label(int l)
{
  d_label = l;
}

std::pair<float, float> DescriptorCollection::normalize()
{
  float max = -1, min = 10;

  foreach (Descriptor const &descriptor, *this)
    foreach (float const &pt, descriptor)
    {
      if (pt < min)
        min = pt;
      
      if (pt > max)
        max = pt;
    }

  assert(!(size() > 0 && (max == -1 or min == 10)));

  foreach (Descriptor &descriptor, *this)
    descriptor.normalize(min, max);
  
  return std::pair<float, float>(min, max);
}

}