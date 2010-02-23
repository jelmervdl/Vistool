#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GLUT/glut.h>
#include <Magick++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "texture.h"

using namespace std;

void initTexture(int window, GLuint * texName, string filename, size_t * twidth, size_t * theight);
void drawTexture(GLuint texName, int twidth, int theight);

#endif
