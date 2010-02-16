#include "ocvConvert.h"

using namespace cv;

namespace OCV_Convert{

  Mat_<float> dataset2Mat(vector <vector <float> > * fl){
    size_t rows, columns;
    rows = fl->size();
    columns = fl->at(0).size();
    Mat matrix(Size(columns,rows),0);
    Mat_<float> fmatrix = (Mat_<float>) matrix;
    for(size_t y = 0; y < rows; ++y)
      for(size_t x = 0; x < columns; ++x){
	fmatrix(x,y) = fl->at(y).at(x);
      }
    return fmatrix;
  }

}
