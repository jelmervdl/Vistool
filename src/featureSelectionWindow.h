#ifndef FEATURESELECTIONWINDOW_H
#define FEATURESELECTIONWINDOW_H

#include "features.h"
#include "toolstate.h"
#include <sstream>

namespace vito{
namespace gui{

class FeatureSelectionWindow : public Singleton<FeatureSelectionWindow> {
protected: 
  GLUI *feature_panel;
public:
  FeatureSelectionWindow();
  void fill();
};

}}

#endif
