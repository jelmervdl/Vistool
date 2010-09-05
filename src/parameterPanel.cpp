#include "parameterPanel.h"

using std::map;
using std::string;

ParameterPanel::ParameterPanel() {
  Parameters *parameters = Parameters::getInstance();
  panel = GLUI_Master.create_glui("parameters", 0, 1325, 150);
  setupFloatVariables( parameters->floatParameters );
  panel->add_column(true);
  setupIntVariables( parameters->intParameters );
}

void ParameterPanel::setupFloatVariables(map<string, float> &float_parameters){
  int total;
  for(map<string, float>::iterator it = float_parameters.begin();
      it != float_parameters.end(); ++it){
    if(total > 15){
      total = 0;
      panel->add_column(false);
    }else
      total++;
    fields.push_back( panel->add_edittext(it->first.c_str(),
					  GLUI_EDITTEXT_FLOAT,
					  (void *) &it->second));
  }
}

void ParameterPanel::setupIntVariables(map<string, int> &int_parameters){
  int total;
  for(map<string, int>::iterator it = int_parameters.begin();
      it != int_parameters.end(); ++it){
    if(total > 15){
      total = 0;
      panel->add_column(false);
    }else
      total++;
    fields.push_back( panel->add_edittext(it->first.c_str(),
					  GLUI_EDITTEXT_INT,
					  (void *) &it->second));
  }
}

