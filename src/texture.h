#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "matrix.h"
#include "dataPoint.h"
#include "glTexture.h"
#include "gradient.h"

class Texture{
 private:
  GLuint txt;
  size_t height;
  size_t width;
  DataPoint * dp;
 public:
  ~Texture();
  Texture(Magick::Image *image, int window);
  Texture(DataPoint * d, int window);
  Texture(VisionToolCore::Matrix<float> * m, int window);
  Texture(VisionToolCore::Matrix<VisionToolFeatures::Gradient> * m, int window);
  int getTXT();
  size_t getHeight();
  size_t getWidth();
  void draw(size_t window_size);
};

#endif
