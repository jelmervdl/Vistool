#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GLUT/glut.h>

#include <stdio.h>
#include <stdlib.h>

//#include <Magick++.h>

#include <png.h>
#include "pngLoad.h"

int setupGLTexture(char *image, long unsigned int width, long unsigned int height, int texName);
void initTexture(GLuint * texName, char *filename, size_t * width, size_t * height);

#endif
