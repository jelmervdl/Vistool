#include "statistics.h"


float Statistics::mean(){
    float total = 0;
    for(Statistics::iterator it = begin();
	it != end();
	++it)
      total += *it;
    return total / (float) size();
}

float Statistics::std(){
  float const cur_mean = mean();
  float total_squared_dist;
  for(Statistics::iterator it = begin();
      it != end();
      ++it){
    const float dist = cur_mean - *it ;
      total_squared_dist += dist * dist;
  }
  return sqrt(total_squared_dist / size());
}
