#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <Magick++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "texture.h"
#include "sift.h"

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
