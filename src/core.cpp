#include "core.h"

using std::cout;
using std::endl;

namespace vito{
namespace print{

void print_svm_problem(svm_problem *problem){
  cout << "printing svm problem:" << endl
       << "size: " << problem->l << endl;
  for(int i = 0; i < problem->l; ++i){
    cout << "label: " << i << " : " << problem->y[i] << endl;
    int node_index = 0;
    while(problem->x[i][node_index].index != -1){
      cout << "value " << problem->x[i][node_index].index << " : " 
	   << problem->x[i][node_index].value << endl;
      node_index++;
    }
  }
}

}
}
