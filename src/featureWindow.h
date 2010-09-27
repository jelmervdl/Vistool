#ifndef FEATUREWINDOW_H
#define FEATUREWINDOW_H

#include <vector>
#include "feature.h"
#include "../libs/glui/glui.h"
#include "features.h"

namespace vito{
namespace gui{

class FeatureWindow {
protected:
  GLUI *window;
public:
  FeatureWindow();
  GLUI *getWindowPointer();
};

}}

#endif
