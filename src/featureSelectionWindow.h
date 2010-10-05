#ifndef FEATURESELECTIONWINDOW_H
#define FEATURESELECTIONWINDOW_H

#include "features.h"
#include "toolState.h"
#include <sstream>

namespace vito{
namespace gui{

class FeatureSelectionWindow : public Singleton<FeatureSelectionWindow> {
public:
  GLUI *feature_panel;

  FeatureSelectionWindow();
  void fill();
};

}}

#endif
