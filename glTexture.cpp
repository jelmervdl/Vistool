#include "glTexture.h"
#include<iostream>

using namespace Magick;
using namespace  std;

void initTexture(int window, GLuint * texName, string filename, size_t * twidth, size_t * theight){
  Image im(filename);
  Blob blob;

  im.magick("RGBA");
  im.write(&blob);
  *twidth = im.columns();
  *theight = im.rows();

  glutSetWindow(window);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, *texName);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, im.columns(), im.rows(), 0, 
	       GL_RGBA, GL_UNSIGNED_BYTE, blob.data());
  glDisable(GL_TEXTURE_2D);
}
