#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <iostream>
#include <math.h>
class Statistics : public std::vector<float>{
public:
  float mean();
  float std();
};
#endif
