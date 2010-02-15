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
#include "dataset.h"

void test();
void loadDataset();
void loadPicture();
void initTextures();
void initGlui();
void display(void);
void start(int argc, char ** argv);
void myGlutIdle( void );

#endif
