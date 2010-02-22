#ifndef OCVCONVERT_H
#define OCVCONVERT_H

#include <vector>
#include "cv.h"
#include <iostream>

using namespace cv;
using namespace std;

namespace OCV_Convert{

  template <typename T> inline Mat_<T> dataset2Mat(vector <vector <T> > * fl){
    size_t rows, columns;
    rows = fl->size();
    columns = fl->at(0).size();
    Mat matrix(Size(columns,rows),0);
    Mat_<T> fmatrix = (Mat_<T>) matrix;
    for(size_t y = 0; y < rows; ++y)
      for(size_t x = 0; x < columns; ++x){
	fmatrix(x,y) = fl->at(y).at(x);
      }
    return fmatrix;
  };
};

#endif OCVCONVERT_H
