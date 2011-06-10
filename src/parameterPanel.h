#ifndef PARAMETERPANEL_H
#define PARAMETERPANEL_H

#include "parameters.h"
#include "../libs/glui/glui.h"
#include <vector>

namespace vito{
namespace gui{

class ParameterPanel{
 private:
  std::vector<GLUI_EditText*> fields;
  GLUI *panel;
  void setupFloatVariables(std::map<std::string, float> &float_parameters);
  void setupIntVariables(std::map<std::string, int>   &int_parameters);
 public:
  ParameterPanel();
};

}}
#endif
