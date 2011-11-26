#include "parameterOptimization.h"
#include "dataset.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::endl;
// Parameter Optimization Functions:

namespace vito{
namespace optimization{

ParameterOptimization::~ParameterOptimization(){
  fout.close();
}

ParameterOptimization::ParameterOptimization(float (*func) (), string const &log_filename)
  : evaluation_function(func),
    best(-9999999.0), 
    fout(log_filename.c_str(), std::ios_base::app){

  add_float_parameter("svm_gamma", -20.0, -0.1, false, true);
  add_float_parameter("svm_C", -20.0, 20.0, false, true);
  //  add_int_parameter("svm_shrinking", 0, 10);
  //add_int_parameter("svm_probabiity", -1, 1, false);

  //add_int_parameter("sift_blur_window", 0, 6, true);
  //add_int_parameter("sift_orientation_directions", 2, 40, true);
  tests_to_run = 144;//2 * pow(kResolution, float_parameters.size() + int_parameters.size());
}

void ParameterOptimization::add_int_parameter(string name, 
					      const int min, 
					      const int max, 
					      const bool positive, 
					      const bool exp){
  Parameters *pars = Parameters::getInstance();
  int *live = &pars->intParameters[name];
  int_parameters.push_back(Parameter<int>(name, min, max, live, positive, exp));
}

void ParameterOptimization::add_float_parameter(string name, 
						const float min, 
						const float max,
						const bool positive,
						const bool exp){
  Parameters *pars = Parameters::getInstance();
  float *live = &pars->floatParameters[name];
  float_parameters.push_back(Parameter<float>(name, min, max, live, positive, exp));
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

void ParameterOptimization::printCurrentParametersToFile(){
  fout <<  "using the following parameters:" << endl;
  for(size_t i = 0; i < int_parameters.size(); ++i)
    fout << "\t" << int_parameters[i].get_name().c_str() 
	 << " is set to " << int_parameters[i].get_value() << endl;
  for(size_t i = 0; i < float_parameters.size(); ++i)
    fout << "\t" << float_parameters[i].get_name().c_str() 
	 << " is set to " << float_parameters[i].get_value() << endl;
}

void ParameterOptimization::printCurrentParameters(){
  printf("using the following parameters:\n");
  for(size_t i = 0; i < int_parameters.size(); ++i)
    printf("\t %s at value %d\n", int_parameters[i].get_name().c_str(),
	   int_parameters[i].get_value());
  for(size_t i = 0; i < float_parameters.size(); ++i)
    printf("\t %s at value %.6f\n", float_parameters[i].get_name().c_str(),
	   float_parameters[i].get_value());
}


void ParameterOptimization::optimize_full_grid(string file, string dest)
{
  cout << "doing full grid " << file << " " << dest << endl;

  // write 
  fout << "dataset: " << Dataset::getPrefferedDatasetName() << endl
       << "input:  " << file << endl
       << "output: " << dest << endl
       << endl;
  
  //Parameters::getInstance()->saveInteger("mode_optimize",1);
  progress = 0;
  
  // if source is not empty, load it as the initial parameters
  if(!file.empty())
  {
    Parameters *pars = Parameters::getInstance();
    pars->readFile(file);
  }
  
  cout << "performing full grid search" << endl;

  started_at = time(NULL);
  
  const int kZooms = 2;

  // iterate the zooms
  for(int current_zoom = 0; current_zoom < kZooms; current_zoom++)
  {
    cout << "at zoom level " << current_zoom << endl;
    optimize_grid_axis(0);
    apply_to_all_parameters(zoom<int>, zoom<float>);
  }

  apply_to_all_parameters(set_to_best<int>, set_to_best<float>);

  // if the destination file is not empty, write the best found parameters
  // to this file.
  if(!dest.empty())
  {
    Parameters::getInstance()->saveInteger("mode_optimize",0);
    Parameters::getInstance()->saveXML(dest);
  }
}

void ParameterOptimization::report_progress(){
  progress++;
  cout << "progress: " << progress << "/" << tests_to_run << " " 
       << ((time(NULL) - started_at) / 	   60.0 / (float) progress) *
    (float) (tests_to_run - progress)
       << " minutes to go" 
       << " time elapsed: " 
       << (time(NULL) - started_at) / 60.0 << " minutes"
       << endl; 
}

void ParameterOptimization::optimize_grid_axis(const size_t at){
  cout << "optimizing grid axis: " << at << endl;
  if(at == int_parameters.size() + float_parameters.size() ){
    cout << "axis a leaf" << endl;
    return;
  }
  else{
    if(at < int_parameters.size()){
      cout << "axis is integer" << endl;
      optimize_int_parameter(int_parameters[at], true, at);
    }
    else{
      cout << "axis is float" << endl;
      optimize_float_parameter(float_parameters[at - int_parameters.size()], true, at);
    }
  }
}

  void ParameterOptimization::optimize(){ // not the full grid,
  const int total_parameters = 
    int_parameters.size() + float_parameters.size();
  for(int epoch = 0; epoch < kIterations; epoch++){
    for(int repet = 0; repet < 2; repet ++){
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
    }
    apply_to_all_parameters(zoom<int>, zoom<float>);
  }
}

void ParameterOptimization::optimize_int_parameter(Parameter<int> &parameter, 
						   const bool fullgrid, 
						   const int step){
  printf("Altering %s\n", parameter.get_name().c_str());
  if(!fullgrid)
    apply_to_all_parameters(set_to_best<int>, set_to_best<float>);
  const int min = parameter.get_min();
  const int max = parameter.get_max();
  float step_size = (float) (max - min) / kResolution;
  for(int res_step = 0; res_step < kResolution + 1; ++res_step){
    const int current_value = (int) (0.5 + min + res_step * step_size);
    std::cout << " current value is: " << current_value << std::endl
	      << "while: min:" << min << " max: " << max << std::endl
	      << "and res step: " << res_step
	      << " and step_size: " << step_size << std::endl;
 
    parameter.set_value(current_value);
    const ParameterSet handle = get_current_parameter_handle();
    if(true || !known(handle)){
      //text output -----------
      std::cout << "going to test with: " << std::endl << std::endl;
      printCurrentParameters();
      std::cout << ".. now .." << std::endl << std::endl;
      float result = evaluation_function();
      report_progress();
      std::cout << "just tested with: " << std::endl;
      printCurrentParameters();
      std::cout << "and that's a fact" << std::endl;
      printf("result: %.6f\n\n", result);
      
      // log results
      if (result > best)
        fout << "result is improvement:";
      else
        fout << "results:";
      
      fout << result << endl;
      printCurrentParametersToFile();
      fout << endl;
      fout.flush();
      //text outpus done ----------

      TestResult res( handle, result);
      current_results.push_back(res);
      if(result > best){
	      printf("improvement: %f -> %f\n", best, result);
	      best = result;
	      apply_to_all_parameters(&set_current_as_best<int>, &set_current_as_best<float>);
      }
    }

    if(fullgrid)
      optimize_grid_axis(step + 1);
  }
}

  void ParameterOptimization::optimize_float_parameter(Parameter<float> &parameter,
						       bool fullgrid,
						       const int step){
  printf("Altering %s\n", parameter.get_name().c_str());
  if(!fullgrid)
    apply_to_all_parameters(&set_to_best<int>, &set_to_best<float>);
  const float min = parameter.get_min();
  const float max = parameter.get_max();
  float step_size = (max - min) / (float)kResolution;
  for(int res_step = 0; res_step < kResolution + 1; ++res_step){
    const float current_value = min + res_step * step_size;
    parameter.set_value(current_value);
    const ParameterSet handle = get_current_parameter_handle();
    if(true || !known(handle)){
      std::cout << "going to test with: " << std::endl << std::endl;
      printCurrentParameters();
      std::cout << ".. now .." << std::endl << std::endl;
      float result = evaluation_function();
      report_progress();
      std::cout << "just tested with: " << std::endl;
      printCurrentParameters();
      std::cout << "and that's a fact" << std::endl;
      printf("result: %.6f\n\n", result);

      // log results
      result > best? fout << "result is improvement:" : fout << "results:";
      fout << result << endl;
      printCurrentParametersToFile();
      fout << endl;
      fout.flush();

      TestResult res( handle, result);
      current_results.push_back(res);
      if(result > best){
	printf("improvement: %f -> %f\n", best, result);
	best = result;
	//parameter.set_current_as_best();
	apply_to_all_parameters(&set_current_as_best<int>, 
				&set_current_as_best<float> );
      }
    }
    if(fullgrid)
      optimize_grid_axis(step + 1);
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
