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
#include "featureExtractor.h"

void extractFeatures();
void test();
void askDataset();
void loadPicture();
void initTextures();
void initGlui();
void display(void);
void start(int argc, char ** argv);
void myGlutIdle( void );
void loadDataset(string location);
void loadCaltech();


#endif
