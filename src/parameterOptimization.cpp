#include "parameterOptimization.h"

using namespace parameter_optimization;
using std::string;
using std::vector;

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

ParameterSet ParameterOptimization::get_current_parameter_handle(){
  vector<int> int_values;
  for(vector<Parameter<int> >::iterator it = int_parameters.begin();
      it != int_parameters.end(); ++it)
    int_values.push_back(it->get_value());
  vector<float> float_values;
  for(vector<Parameter<float> >::iterator it = float_parameters.begin();
      it != float_parameters.end(); ++it)
    float_values.push_back(it->get_value());
  return ParameterSet(int_values, float_values);
}

void ParameterOptimization::optimize(){
  const int total_parameters = 
    int_parameters.size() + float_parameters.size();
  for(int epoch = 0; epoch < iterations; epoch++){
    for(int parameter_index = 0; 
	parameter_index < total_parameters;
	++parameter_index){

      if(parameter_index < (int) int_parameters.size()){
	Parameter<int> &parameter = 
	  int_parameters[parameter_index];
	printf("Parameter name is %s\n", parameter.get_name().c_str());
	const int min = parameter.get_min();
	const int max = parameter.get_max();
	float step_size = (max - min) / resolution;
	for(int res_step = 0; res_step < resolution; ++res_step){
	  const int current_value = (int) (0.5 + min + res_step * step_size);
	  const ParameterSet handle= get_current_parameter_handle();
	  if(!known(handle)){
	    parameter.set_value(current_value);
	    float result = evaluation_function();
	    TestResult res( handle, result);
	    current_results.push_back(res);
	  }
	}
      } 
      else{
	Parameter<float> &parameter = 
	  float_parameters[parameter_index - int_parameters.size()];
	printf("Parameter name is %s\n", parameter.get_name().c_str());
      }

    }
  }
}

bool ParameterOptimization::known(const ParameterSet &handle){
  for(vector<TestResult>::iterator it = current_results.begin();
      it != current_results.end(); ++it){
    const ParameterSet &current_handle = it->parameter_set;
    if(handle.equals(current_handle))
      return true;
  } 
  return false;
}

bool ParameterSet::equals(const ParameterSet &other) const{
  if(ints.size() != other.ints.size() || floats.size() != other.floats.size())
    return false;
  for(size_t i = 0; i <  ints.size(); ++i)
    if(ints[i] != other.ints[i])
	return false;
  for(size_t i = 0; i <  floats.size(); ++i)
    if(floats[i] != other.floats[i])
	return false;
  return true;
}
