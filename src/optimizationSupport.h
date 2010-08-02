#ifndef OPTIMIZATION_SUPPORT
#define OPTIMIZATION_SUPPORT

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

namespace vito{
namespace optimization{

  template <class Type> class Parameter{
  private:
    std::string name;
    Type        best;
    Type        min;
    Type        max;
    Type        *live_value;
    bool positive;
    bool expon;

  public:  
    Parameter(std::string _name, Type _min, Type _max, Type *live,
	      bool force_positive, bool _expon = false): 
      name(_name), min(_min), max(_max), 
      live_value(live), positive(force_positive), expon(_expon){
      expon? best = pow(2, min) : best = min;
    }    

    std::string get_name() const {
      return name;
    }
    Type        get_min() const {
      if(positive && min < 0)
	return 0.0000001;
      return min;

    }
    Type        get_max() const {
      if(positive && max < 0)
	return 0.0000001;
      return max;
    }
    Type get_value() const {
      return *live_value;
    }
    void set_value(Type new_value){
      std::cout << "I want to set to" << new_value << std::endl;
      if(expon) std::cout << "it's quadratic so, that means it'll be set to: "
			  << pow(2,new_value) << std::endl;
      expon? *live_value = pow(2, new_value) : *live_value = new_value;
    }
    void set_current_as_best(){
      best = *live_value;
    }
    void set_to_best(){
      std::cout << "live_value of " << name << " is now: " << *live_value << 
	" setting it to the supposed best: " << best << std::endl;
      *live_value = best;
      std::cout << "live value is now " << *live_value << std::endl;
    }
    void zoom(const float zoom_factor){
      const Type margin = (max - min) * 0.5 / zoom_factor;
      Type best_;
      expon? best_ = log(best) : best_ = best;
      if(min < best_ - margin) 
	min = best_ - margin;
      if(max > best_ + margin)
	max = best_ + margin;
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

}}

#endif
