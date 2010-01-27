#ifndef GLUIVISIONTOOL_H
#define GLUIVISIONTOOL_H

#include <stdio.h>
#include <GLUT/glut.h>
#include "glui.h"
#include "fd.h"
#include "glTexture.h"

void loadPicture();
void initGlui();
void display(void);
void start(int argc, char ** argv);
void initTextures();
void drawTexture(GLuint texName, int twidth, int theight);




#endif
