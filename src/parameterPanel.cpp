#include "parameterPanel.h"


ParameterPanel::ParameterPanel() {
  Parameters *parameters = Parameters::getInstance();
  panel = GLUI_Master.create_glui("parameters", 0, 800, 0);
  setupFloatVariables( parameters->floatParameters );
  setupIntVariables( parameters->intParameters );
}

void ParameterPanel::setupFloatVariables(map<string, float> &float_parameters){
  for(map<string, float>::iterator it = float_parameters.begin();
      it != float_parameters.end(); ++it){
    fields.push_back( panel->add_edittext(it->first.c_str(),
					  GLUI_EDITTEXT_FLOAT,
					  (void *) &it->second));
  }
}

void ParameterPanel::setupIntVariables(map<string, int> &int_parameters){
  for(map<string, int>::iterator it = int_parameters.begin();
      it != int_parameters.end(); ++it){
    fields.push_back( panel->add_edittext(it->first.c_str(),
					  GLUI_EDITTEXT_INT,
					  (void *) &it->second));
  }
}

