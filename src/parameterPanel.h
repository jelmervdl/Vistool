#ifndef PARAMETERPANEL_H
#define PARAMETERPANEL_H

#include "../libs/glui/glui.h"
#include <vector>
#include <map>
#include <string>

namespace vito{
namespace gui{

class ParameterPanel
{

private:
  GLUI *panel;
  std::vector<GLUI_EditText *> fields;
  
  template <class T>
  GLUI_Panel *setupVariables(std::string const &name,
    std::map<std::string, T> &parameters, int data_type);

public:
  ParameterPanel();
};

}}
#endif
