#ifndef PARAMETERPANEL_H
#define PARAMETERPANEL_H

#include "parameters.h"
#include "../libs/glui/glui.h"
#include <vector>

namespace vito{
namespace gui{

class ParameterPanel
{

private:
  std::vector<GLUI_EditText*> fields;
  GLUI *panel;
  
  template <class T>
  void setupVariables(std::map<std::string, T> &parameters, int data_type);

public:
  ParameterPanel();
};

}}
#endif
