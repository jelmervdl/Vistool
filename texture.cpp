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

void Texture::draw(){
  drawTexture(txt, (int) width, (int) height);
}

Texture::~Texture(){
  using namespace std;
  glDeleteTextures(1, &txt);
}
