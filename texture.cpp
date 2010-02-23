#include "texture.h"

Texture::Texture(DataPoint * d, int window): dp(d){
  glGenTextures(1, &txt);
  initTexture(window, &txt, d->getImageURL(), &width, &height);
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
