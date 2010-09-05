#ifndef KEYPOINT_H
#define KEYPOINT_H

#include <iostream>
#include <vector>

namespace sift{

class KeyPoint{
 private:
  size_t center_x;
  size_t center_y;
  float scale;
  float angle;
 public:
  KeyPoint(size_t x, size_t y, float scale);
  size_t get_center_x() const;
  size_t get_center_y() const;
  float get_scale() const;
};


 std::vector<KeyPoint> divideIntoKeypoints(size_t width, size_t height, 
				     size_t x_points, size_t y_points);
}
#endif
