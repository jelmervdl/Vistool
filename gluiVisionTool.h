#ifndef GLUIVISIONTOOL_H
#define GLUIVISIONTOOL_H

#include <stdio.h>
#include <GLUT/glut.h>
#include "glui.h"
#include "fileDialog.h"
#include "glTexture.h"

void display(void);
void start(int argc, char ** argv);
void initTextures(char * dir_add);
void drawTexture(GLuint texName, int twidth, int theight);




#endif
