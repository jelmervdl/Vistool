#ifndef OPTIMIZATION_SUPPORT
#define OPTIMIZATION_SUPPORT

#include <iostream>
#include <string>
#include <vector>

namespace parameter_optimization{

  template <class Type> class Parameter{
  private:
    std::string name;
    Type        best;
    Type        min;
    Type        max;
    Type        *live_value;

  public:  
    Parameter(std::string _name, Type _min, Type _max, Type *live): 
      name(_name), min(_min), max(_max), live_value(live){
      best = min;
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
    void set_current_as_best(){
      std::cout << "yeah... " << best << std::endl;
      best = *live_value;
      std::cout << "yeah... " << best << std::endl;
    }
    void set_to_best(){
      *live_value = best;
    }
  };

  class ParameterSet{
  public:
    std::vector<int> ints;
    std::vector<float> floats;
    ParameterSet(std::vector<int> _ints, std::vector<float> _floats) : 
      ints(_ints), floats(_floats) {};
    bool equals(const ParameterSet &other) const ;
    void print() const;
  };

  class TestResult{
  public:
    ParameterSet parameter_set;
    float result;
    TestResult(ParameterSet _set, float _result) : 
      parameter_set(_set), result(_result) {};
  };

}

#endif
