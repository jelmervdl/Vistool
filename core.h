#ifndef CORE_H
#define CORE_H

#include <vector>

using namespace std;

namespace states {
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


namespace VisionCore{

  template <typename T>  vector<T*> ptrDeMorgan(vector <T> * vec){
    vector<T*> ret;
    for(size_t i = 0; i < vec->size(); ++i)
      ret.push_back(&(vec->at(i)));
    return ret;
  };

};

#endif
