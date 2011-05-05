#ifndef PARAMETEROPTIMIZATION
#define PARAMETEROPTIMIZATION

#include <fstream>
#include "optimizationSupport.h"
#include "parameters.h"
#include "singleton.h"

namespace vito{
namespace optimization{
 

  const int kIterations  = 3;
  const float kZoom = 2.5;
  const int kResolution = 7;

  
  class ParameterOptimization {
  private:
    //evaluation function used to evaluate the parameters
    int progress;
    int tests_to_run;
    time_t started_at;
    float                        (*evaluation_function) ();
    float                          best;
    std::ofstream fout;
    std::vector<TestResult>        current_results; 
    std::vector<Parameter<int> >   int_parameters;
    std::vector<Parameter<float> > float_parameters;

    // add a parameters to optimize
    void report_progress();

    void         add_int_parameter(std::string name, 
				   const int min, 
				   const int max,
				   const bool positive = false,
				   const bool exp = false);

    void         add_float_parameter(std::string name, 
				     const float min, 
				     const float max, 
				     const bool positive = false,
				     const bool exp = false);

    // print the parameters
    void         printCurrentParameters();
    void         printCurrentParametersToFile();
    void         set_all_to_best();
    void         set_best_to_current();
    ParameterSet get_current_parameter_handle();
    bool         known(const ParameterSet &handle);
    void         optimize_int_parameter  (Parameter<int>   &parameter,
					  bool fullgrid = false,
					  const int step = 0);
    void         optimize_float_parameter(Parameter<float> &parameter, 
					  bool fullgrid = false,
					  const int step = 0);
    void         apply_to_all_parameters(void (*int_func) (Parameter<int>*),
					 void (*fl_func)  (Parameter<float>*));
  public:
                 ParameterOptimization( float(*func)() );
                ~ParameterOptimization();
    void         optimize();
    void         optimize_full_grid(std::string str = "", std::string dest = "");
    void         optimize_grid_axis(const size_t at);
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
}}

#endif
