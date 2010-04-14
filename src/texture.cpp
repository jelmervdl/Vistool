#include "texture.h"

using Magick::Image;

namespace vito{
namespace gui{

using features::Gradient;


Texture::Texture(Image *image, int window){
  glGenTextures(1, &txt);
  initTexture(window, &txt, image, &width, &height);
}

Texture::Texture(DataPoint * d, int window): dp(d){
  glGenTextures(1, &txt);
  initTexture(window, &txt, d->get_image_url(), &width, &height);
}

Texture::Texture(Matrix<float> * m, int window){
  glGenTextures(1, &txt);
  initTexture(window, &txt, m, &width, &height);
}

Texture::Texture(Matrix<Gradient> * m, int window){
  glGenTextures(1, &txt);
  initTexture(window, &txt, m, &width, &height);
}

int Texture::getTXT(){
  return txt;
}

size_t Texture::getHeight(){
  return height;
}

size_t Texture::getWidth(){
  return width;
}

void Texture::draw(size_t window_size){
  size_t nheight, nwidth;

  nheight = window_size;
  nwidth = width * ((double) window_size / (double) height);
  if (nwidth > window_size){
    nheight = window_size * (nheight / (double) nwidth);
    nwidth = window_size;
  }
  drawTexture(txt, (int) nwidth, (int) nheight);
}

Texture::~Texture(){
  using namespace std;
  glDeleteTextures(1, &txt);
}

}}
