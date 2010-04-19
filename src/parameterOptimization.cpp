#include "parameterOptimization.h"


using std::string;
using std::vector;

// Parameter Optimization Functions:

namespace vito{
namespace optimization{

ParameterOptimization::ParameterOptimization(float (*func) ())
  : evaluation_function(func), best(-9999999.0){

  add_float_parameter("svm_C", 0.0, 100.0);
  add_float_parameter("svm_coef0", 0.0, 30.0);  
  add_float_parameter("svm_eps", 0.0003, 1.5);
  add_float_parameter("svm_gamma", 5.0, 100.0, true);
  add_int_parameter("svm_degree", 5, 30, true);

  //  add_int_parameter("svm_shrinking", 0, 10);
  //add_int_parameter("svm_probabiity", -1, 1, false);

}

void ParameterOptimization::add_int_parameter(string name, const int min, 
					      const int max, const bool positive){
  Parameters *pars = Parameters::getInstance();
  int *live = &pars->intParameters[name];
  int_parameters.push_back(Parameter<int>(name, min, max, live, positive));
}

void ParameterOptimization::add_float_parameter(string name, const float min, 
						const float max, const bool positive){
  Parameters *pars = Parameters::getInstance();
  float *live = &pars->floatParameters[name];
  float_parameters.push_back(Parameter<float>(name, min, max, live, positive));
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

void ParameterOptimization::printCurrentParameters(){
  printf("using the following parameters:\n");
  for(size_t i = 0; i < int_parameters.size(); ++i)
    printf("\t %s at value %d\n", int_parameters[i].get_name().c_str(),
	   int_parameters[i].get_value());
  for(size_t i = 0; i < float_parameters.size(); ++i)
    printf("\t %s at value %.2f\n", float_parameters[i].get_name().c_str(),
	   float_parameters[i].get_value());
}

void ParameterOptimization::optimize(){
  const int total_parameters = 
    int_parameters.size() + float_parameters.size();
  for(int epoch = 0; epoch < kIterations; epoch++){
    for(int parameter_index = 0; 
	parameter_index < total_parameters;
	++parameter_index){

      if(parameter_index < (int) int_parameters.size()){
	optimize_int_parameter(int_parameters[parameter_index]);
      } 
      else{
	optimize_float_parameter( float_parameters[parameter_index - 
						   int_parameters.size()]);
	Parameter<float> &parameter = 
	  float_parameters[parameter_index - int_parameters.size()];
	printf("Parameter name is %s\n", parameter.get_name().c_str());
      }
    }
    apply_to_all_parameters(zoom<int>, zoom<float>);
  }
}

void ParameterOptimization::optimize_int_parameter(Parameter<int> &parameter){
  printf("Altering %s\n", parameter.get_name().c_str());
  apply_to_all_parameters(set_to_best<int>, set_to_best<float>);
  const int min = parameter.get_min();
  const int max = parameter.get_max();
  float step_size = (max - min) / kResolution;
  for(int res_step = 0; res_step < kResolution + 1; ++res_step){
    const int current_value = (int) (0.5 + min + res_step * step_size);
    parameter.set_value(current_value);
    const ParameterSet handle = get_current_parameter_handle();
    if(true || !known(handle)){
      float result = evaluation_function();
      printCurrentParameters();
      printf("result: %.2f\n\n", result);
      TestResult res( handle, result);
      current_results.push_back(res);
      if(result > best){
	printf("improvement: %f -> %f\n", best, result);
	best = result;
	apply_to_all_parameters(&set_current_as_best<int>, 
				&set_current_as_best<float> );
      }
    }
  }
}

void ParameterOptimization::optimize_float_parameter(Parameter<float> &parameter){
  printf("Altering %s\n", parameter.get_name().c_str());
  apply_to_all_parameters(&set_to_best<int>, &set_to_best<float>);
  const float min = parameter.get_min();
  const float max = parameter.get_max();
  float step_size = (max - min) / (float)kResolution;
  for(int res_step = 0; res_step < kResolution + 1; ++res_step){
    const float current_value = min + res_step * step_size;
    parameter.set_value(current_value);
    const ParameterSet handle = get_current_parameter_handle();
    if(true || !known(handle)){
      float result = evaluation_function();
      printCurrentParameters();
      printf("result: %.2f\n\n", result);
      TestResult res( handle, result);
      current_results.push_back(res);
      if(result > best){
	printf("improvement: %f -> %f\n", best, result);
	best = result;
	apply_to_all_parameters(&set_current_as_best<int>, 
				&set_current_as_best<float> );
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

void ParameterOptimization::apply_to_all_parameters(void (*int_func)
						    (Parameter<int>*),
						    void (*fl_func)
						    (Parameter<float>*) ){
  { 
    typedef vector<Parameter<int> >::iterator par_it;
    for(par_it it = int_parameters.begin(); 
	it != int_parameters.end(); ++it)
      int_func(&*it);
  } {
    typedef vector<Parameter<float> >::iterator par_fl;
    for(par_fl it = float_parameters.begin(); 
	it != float_parameters.end(); ++it)
      fl_func(&*it);
  }
}
}}
