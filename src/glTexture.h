#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GLUT/glut.h>
#include <Magick++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "gradient.h"

namespace vito{
namespace gui{

void initTexture(int window, GLuint *texName,
		 std::string filename, 
		 size_t *twidth, size_t *theight);
void initTexture(int window, GLuint *texName,
		 Magick::Image *im,
		 size_t *twidth, size_t *theight);
void initTexture(int window, GLuint *texName,
		 Magick::Blob  *blob,   size_t *twidth, size_t *theight);
void initTexture(int window, GLuint *texName, Matrix<float> * im,
		 size_t *twidth, size_t *theight);
void initTexture(int window, GLuint *texName, 
		 Matrix<features::Gradient> *matrix,
		 size_t *width, size_t *height);
void drawTexture(GLuint texName, int twidth, int theight);

}}

#endif
