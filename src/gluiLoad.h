#ifndef GLUILOAD_H
#define GLUILOAD_H

#include "fd.h"
#include "toolState.h"
#include "gluiView.h"
#include <sstream>

namespace vito{
namespace gui{

void loadPicture();
void loadDataset(std::string location);
void loadCaltech();
void askDataset();

}}

#endif
