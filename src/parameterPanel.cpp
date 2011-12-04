#include "parameterPanel.h"
#include <map>
#include <string>

namespace vito{
namespace gui{

ParameterPanel::ParameterPanel()
{
  Parameters *parameters = Parameters::getInstance();
  panel = GLUI_Master.create_glui("parameters", 0, 1325, 150);

  setupVariables(parameters->floatParameters, GLUI_EDITTEXT_FLOAT);
  
  panel->add_column(true);
  
  setupVariables(parameters->intParameters, GLUI_EDITTEXT_INT);
}

template <class T>
void ParameterPanel::setupVariables(std::map<std::string, T> &parameters, int data_type){
  int total;
  
  for (typename std::map<std::string, T>::iterator it = parameters.begin();
    it != parameters.end(); ++it)
  {
    if(total > 15)
    {
      total = 0;
      panel->add_column(false);
    }
    else
      total++;
    
    fields.push_back(
      panel->add_edittext(it->first.c_str(), data_type, (void *) &it->second));
  }
}

}}
