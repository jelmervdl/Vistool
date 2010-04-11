#include "parameterOptimization.h"

using namespace parameter_optimization;
using std::string;

ParameterOptimization::ParameterOptimization(float (*func) ())
  : evaluation_function(func){
  add_float_parameter("test", 0.0, 5.0);
  
}

void ParameterOptimization::add_int_parameter(string name, const int min, 
					      const int max){
  Parameters *pars = Parameters::getInstance();
  int *live = &pars->intParameters[name];
  int_parameters.push_back(Parameter<int>(name, min, max, live));
}

void ParameterOptimization::add_float_parameter(string name, const float min, 
					      const float max){
  Parameters *pars = Parameters::getInstance();
  float *live = &pars->floatParameters[name];
  float_parameters.push_back(Parameter<float>(name, min, max, live));
}

void ParameterOptimization::optimize(){
  const int total_parameters = 
    int_parameters.size() + float_parameters.size();
  for(int epoch = 0; epoch < epochs; epoch++){
    for(int parameter_index = 0; 
	parameter_index < total_parameters;
	++parameter_index){

      if(parameter_index < (int) int_parameters.size()){
	Parameter<int> &parameter = 
	  int_parameters[parameter_index];
	printf("Parameter name is %s\n", parameter.get_name().c_str());
      } 
      else{
	Parameter<float> &parameter = 
	  float_parameters[parameter_index - int_parameters.size()];
	printf("Parameter name is %s\n", parameter.get_name().c_str());
      }

    }
  }
}
