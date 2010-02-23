#ifndef GLUIVISIONTOOL_H
#define GLUIVISIONTOOL_H

#include <stdio.h>
#include <GLUT/glut.h>
#include <iostream>
#include <string> 

#include <math.h>
#include "glui.h"
#include "fd.h"
#include "glTexture.h"
#include "fileManagement.h"
#include "dataset.h"
#include "featureExtractor.h"
#include "texture.h"

//start the gui app:
void start(int argc, char ** argv);
void initTextures();
void initGlui();
void setupWindow();
void setupOpenGL();
void nextPage();

//glut functions
void display(void);
void myGlutIdle( void );

// buttons functions for image and dset loading
void loadPicture();
void loadDataset(string location);
void loadCaltech();

// more button functions
void test();
void extractFeatures();
void askDataset();
void quitf();

void viewDataset();
void setViewSelection();
void refreshTexture(size_t a =0);
void nextPage();
#endif
