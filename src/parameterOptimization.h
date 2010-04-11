#ifndef PARAMETEROPTIMIZATION
#define PARAMETEROPTIMIZATION

#include "parameters.h"
#include "singleton.h"
#include <vector>
#include <string>

namespace parameter_optimization{

  const int epochs  = 5;
  const float zoom  = 1.5;
  const int resolution = 5;
  
  template <class Type> class Parameter{
  private:
    std::string name;
    Type        min;
    Type        max;
    Type        *live_value;

  public:  
    Parameter(std::string _name, Type _min, Type _max, Type *live): 
      name(_name), min(_min), max(_max), live_value(live){
    }    
    std::string get_name(){
      return name;
    }
    Type        get_min(){
      return min;
    }
    Type        get_max(){
      return max;
    }
  };
  
  class ParameterOptimization {
  private:
    float (*evaluation_function) ();
    std::vector<Parameter<int> > int_parameters;
    std::vector<Parameter<float> > float_parameters;
    void add_int_parameter(std::string name, const int min, const int max);
    void add_float_parameter(std::string name, const float min, const float max);
  public:
    ParameterOptimization( float(*func)() );
    void optimize();
  };
}

#endif
