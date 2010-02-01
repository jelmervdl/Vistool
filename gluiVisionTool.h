#ifndef GLUIVISIONTOOL_H
#define GLUIVISIONTOOL_H

#include <stdio.h>
#include <GLUT/glut.h>
#include "glui.h"
#include "fd.h"
#include "glTexture.h"
#include <iostream>
#include <string> 

void loadPicture();
void initGlui();
void display(void);
void start(int argc, char ** argv);
void initTextures();
void drawTexture(GLuint texName, int twidth, int theight);
void loadPicture();
void myGlutIdle( void );

#endif
