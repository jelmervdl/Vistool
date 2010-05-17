#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "matrix.h"
#include "dataPoint.h"
#include "glTexture.h"
#include "gradient.h"

namespace vito{
namespace gui{

class Texture{
 private:
  GLuint txt;
  size_t height, width;
  DataPoint * dp;

 public:
  // Constructors:
         Texture(Magick::Image *image, int window);
         Texture(DataPoint * d, int window);
         Texture(Matrix<float> * m, int window);
         Texture(Matrix<features::Gradient> * m, int window);

  // kill the texture for memory's sake... a proper destructor isn't
  // possible if intending to use vector because vectors delete
  // temporary object
  void   destroyTexture();

  // get texture adress
  int    getTXT() const;

  // get aspects
  size_t getHeight() const ;
  size_t getWidth() const ;

  // draw the texture given a window size
  void   draw(size_t window_size);
};


}}
#endif
