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
  float total_squared_dist = 0.0;
  for(Statistics::iterator it = begin(); it != end(); ++it){
    const float dist = cur_mean - *it ;
    total_squared_dist += dist * dist;
  }
  return sqrt(total_squared_dist / size());
}

namespace studentTTest{

float exceedingChance(float m1, float std1, size_t n, 
		       float m2, float std2, size_t m){
  float t = student_t_test(m1, std1,n, m2, std2, m);
  float dof = degreesOfFreedom(std1 * std1, n, std2 * std2, m);
  return exceedingChance(t, dof); 
}

float exceedingChance(float t, float dof){
  boost::math::students_t_distribution<float> tdistribution(dof);
  return boost::math::cdf<float>(tdistribution, t);
}

float pooledVariance(float v1, size_t n, float v2, size_t m){
  if (n + m > 2) return sqrt(((n - 1)  * v1 + (m - 1) * v2) /
			            (float) (n + m - 2));
  else           return 0.0;
}

float degreesOfFreedom(float v1, float n, float v2, float m){
  float r1 = v1 / n, r2 = v2 / m;
  return ((r1 + r2) * (r1 + r2)) / 
    (
     ((r1 * r1) / (n - 1)) +  ((r2 * r2) / (m - 1))
     );
}

float student_t_test(float m1, float std1, size_t n, 
		     float m2, float std2, size_t m){
  float v1 = std1 * std1;
  float v2 = std2 * std2;
  float s = pooledVariance(v1, n, v2, m);
  float t = 
    (m1 - m2) /
    (s * sqrt((1.0 / (float) n) + (1.0 / (float) m)));
  return t;
}
void perform(){
  student_t_test(69.0, sqrt(255.8), 10,
		 73.0, sqrt(212.7), 15);
}
}

