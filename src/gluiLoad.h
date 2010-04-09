#ifndef GLUILOAD_H
#define GLUILOAD_H

#include "fd.h"
#include "toolState.h"
#include "gluiView.h"

namespace VisionToolGUI {

void loadPicture();
void loadDataset(std::string location);
void loadCaltech();
void askDataset();

}

#endif
