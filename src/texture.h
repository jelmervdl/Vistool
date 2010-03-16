#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

#include "dataPoint.h"
#include "glTexture.h"

class Texture{
 private:
  GLuint txt;
  size_t height;
  size_t width;
  DataPoint * dp;
 public:
  ~Texture();
  Texture(DataPoint * d, int window);
  int getTXT();
  size_t getHeight();
  size_t getWidth();
  void draw(size_t window_size);
};

#endif
