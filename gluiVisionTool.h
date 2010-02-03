#ifndef GLUIVISIONTOOL_H
#define GLUIVISIONTOOL_H

#include <stdio.h>
#include <GLUT/glut.h>
#include <iostream>
#include <string> 

#include "glui.h"
#include "fd.h"
#include "glTexture.h"
#include "fileManagement.h"

void loadPicture();
void loadDataset();
void initGlui();
void display(void);
void start(int argc, char ** argv);
void initTextures();
void drawTexture(GLuint texName, int twidth, int theight);
void myGlutIdle( void );

#endif
