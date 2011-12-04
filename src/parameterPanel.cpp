#include "parameterPanel.h"

#include "parameters.h"
#include <map>
#include <string>

namespace vito{
namespace gui{

ParameterPanel::ParameterPanel()
{
  Parameters *parameters = Parameters::getInstance();
  panel = GLUI_Master.create_glui("parameters", 0, 1325, 150);

  setupVariables("Float variables",
    parameters->floatParameters, GLUI_EDITTEXT_FLOAT);
  
  panel->add_column(true);
  
  setupVariables("Integer variables",
    parameters->intParameters, GLUI_EDITTEXT_INT);
}

template <class T>
GLUI_Panel *ParameterPanel::setupVariables(std::string const &name,
  std::map<std::string, T> &parameters, int data_type)
{
  int total;
  GLUI_Panel *group = panel->add_panel(name.c_str());
  
  for (typename std::map<std::string, T>::iterator it = parameters.begin();
    it != parameters.end(); ++it)
  {
    if (total++ > 15)
    {
      total = 0;
      panel->add_column_to_panel(group, false);
    }
    
    fields.push_back(
      panel->add_edittext_to_panel(group, it->first.c_str(),
        data_type, (void *) &it->second));
  }

  return group;
}

}}
