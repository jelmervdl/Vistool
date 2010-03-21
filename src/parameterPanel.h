#ifndef PARAMETERPANEL_H
#define PARAMETERPANEL_H

#include "parameters.h"
#include "glui.h"

class ParameterPanel{
 private:
  vector<GLUI_EditText*> fields;
  GLUI *panel;
  void setupFloatVariables(map<string, float> &float_parameters);
  void setupIntVariables(map<string, int>   &int_parameters);
 public:
  ParameterPanel();
};

#endif
