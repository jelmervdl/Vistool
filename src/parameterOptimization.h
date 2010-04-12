#ifndef PARAMETEROPTIMIZATION
#define PARAMETEROPTIMIZATION

#include "optimizationSupport.h"
#include "parameters.h"
#include "singleton.h"

namespace parameter_optimization{
 
  const int kIterations  = 5;
  const float kZoom= 1.5;
  const int kResolution = 5;
  
  class ParameterOptimization {
  private:
    //evaluation function used to evaluate the parameters
    float (*evaluation_function) ();
    float best;

    std::vector<TestResult> current_results; 
    std::vector<Parameter<int> > int_parameters;
    std::vector<Parameter<float> > float_parameters;

    void add_int_parameter(std::string name, const int min, const int max);
    void add_float_parameter(std::string name, const float min, const float max);
    void printCurrentParameters();
    void set_all_to_best();
    void set_best_to_current();
    ParameterSet get_current_parameter_handle();
    bool known(const ParameterSet &handle);
    void optimize_int_parameter  (Parameter<int>   &parameter);
    void optimize_float_parameter(Parameter<float> &parameter);
    void apply_to_all_parameters(void (*int_func) (Parameter<int>*),
				 void (*fl_func)  (Parameter<float>*));
  public:
    ParameterOptimization( float(*func)() );
    void optimize();
  };

  template<class Type> void set_to_best(Parameter<Type> *parameter){
    parameter->set_to_best();
  }
  template<class Type> void set_current_as_best(Parameter<Type> *parameter){
    parameter->set_current_as_best();
  }
  template<class Type> void zoom(Parameter<Type> *parameter){
    parameter->zoom(kZoom);
  }
}

#endif
