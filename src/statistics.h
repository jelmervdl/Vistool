#ifndef STATISTICS_H
#define STATISTICS_H

#include <boost/math/distributions/students_t.hpp>
#include <vector>
#include <iostream>
#include <math.h>
class Statistics : public std::vector<float>{
public:
  float mean();
  float std();
};

namespace studentTTest{
float exceedingChance(float m1, float std1, size_t n, 
		      float m2, float std2, size_t m);
float exceedingChance(float t, float dof);
float pooledVariance(float v1, size_t n, float v2, size_t m);
float student_t_test(float m1, float std1, size_t n, 
		     float m2, float std2, size_t m);
float degreesOfFreedom(float v1, float n, float v2, float m);
void perform();
}

#endif

