#ifndef PARAMETEROPTIMIZATION
#define PARAMETEROPTIMIZATION

#include "parameters.h"
#include "singleton.h"
#include <vector>
#include <string>

namespace parameter_optimization{

  const int iterations  = 5;
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
    std::string get_name() const {
      return name;
    }
    Type        get_min() const {
      return min;
    }
    Type        get_max() const {
      return max;
    }
    Type get_value() const {
      return *live_value;
    }
    void set_value(Type new_value){
      *live_value = new_value;
    }
  };

  class ParameterSet{
  public:
    std::vector<int> ints;
    std::vector<float> floats;
    ParameterSet(std::vector<int> _ints, std::vector<float> _floats) : 
      ints(_ints), floats(_floats) {};
    bool equals(const ParameterSet &other) const ;
  };

  class TestResult{
  public:
    ParameterSet parameter_set;
    float result;
    TestResult(ParameterSet _set, float _result) : 
      parameter_set(_set), result(_result) {};
  };
  
  class ParameterOptimization {
  private:
    //evaluation function used to evaluate the parameters
    float (*evaluation_function) ();

    std::vector<TestResult> current_results; 
    std::vector<Parameter<int> > int_parameters;
    std::vector<Parameter<float> > float_parameters;

    void add_int_parameter(std::string name, const int min, const int max);
    void add_float_parameter(std::string name, const float min, const float max);
    ParameterSet get_current_parameter_handle();
    bool known(const ParameterSet &handle);
  public:
    ParameterOptimization( float(*func)() );
    void optimize();
  };
}

#endif
