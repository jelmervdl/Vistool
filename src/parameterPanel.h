#ifndef PARAMETERPANEL_H
#define PARAMETERPANEL_H

#include "parameters.h"
#include "glui.h"

class ParameterPanel{
 private:
  std::vector<GLUI_EditText*> fields;
  GLUI *panel;
  void setupFloatVariables(std::map<std::string, float> &float_parameters);
  void setupIntVariables(std::map<std::string, int>   &int_parameters);
 public:
  ParameterPanel();
};

#endif
