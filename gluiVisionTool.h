#ifndef GLUIVISIONTOOL_H
#define GLUIVISIONTOOL_H

#include <stdio.h>
#include <GLUT/glut.h>
#include "glui.h"

class GluiVisionTool{
 public: 
  void start();
  GluiVisionTool(int argc, char ** argv);
 private:
  int main_window;
};

#endif
