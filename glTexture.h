#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GLUT/glut.h>
#include <Magick++.h>

#include <stdio.h>
#include <stdlib.h>

#include <png.h>
#include "pngLoad.h"

int setupGLTexture(char *image, long unsigned int width, long unsigned int height, int texName);
void initTexture(int window, GLuint * texName, char *filename, size_t * twidth, size_t * theight);

#endif
