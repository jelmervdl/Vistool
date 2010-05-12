#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <vector>
#include "svm.h"

namespace vito{

namespace print{

void print_svm_problem(svm_problem *problem);

}

namespace states{
  enum EnabledClassifier{
    NearestNeighbor,
    SupportVectorMachine
  };

  enum DisplayModifier{
    No_Modifier,
    Show_Gradient,
    Show_Sift
  };
  enum DatasetOnDisplay {
    Enabled_Datasets,
    Training_DataPoints,
    Testing_DataPoints,
    Correct,
    Incorrect,
    Particular_Category
  };
  
  enum DisplayMode {
    Nothing,
    Single_Image,
    Show_Dataset
  };
};


namespace ptr{

  template <typename T>  std::vector<T*> ptrDeMorgan(std::vector <T> * vec){
    std::vector<T*> ret;
    for(size_t i = 0; i < vec->size(); ++i)
      ret.push_back(&(vec->at(i)));
    return ret;
  };



};
}
#endif
