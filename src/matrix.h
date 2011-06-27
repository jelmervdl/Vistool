#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

namespace vito{

template<class Type> class Matrix{
 private:
  size_t width, height;
 public:
  Type * values;
  //constructor
        ~Matrix();
         Matrix(size_t width_, size_t height_);

  // get lengths
  size_t get_width() const;
  size_t get_height() const;

  // get a value at an index
  Type   at(size_t x, size_t y) const;
  Type&  at(size_t x, size_t y);

  //  print the matrix values assuming they have some '<<' operator
  void   print() const; 
};

// implementations

template <class Type> Matrix<Type>::~Matrix(){
  delete [] values;
}

template <class Type> Matrix<Type>::Matrix(size_t width_, 
					   size_t height_) : 
  width(width_), height(height_){
  values = new Type[width * height];
}

template <class Type> Type& Matrix<Type>::at(size_t x, size_t y){
    return values[x + width * y];
}

template <class Type> Type Matrix<Type>::at(size_t x, size_t y) const {
    return values[x + width * y];
}


template <class Type> void Matrix<Type>::print() const {
  for(size_t x = 0; x < width; ++x){
    for (size_t y = 0; y < height; ++y){
      std::cout << values[x + y * width] << " ";
      }
    std::cout << std::endl;
  }
}

template <class Type> size_t Matrix<Type>::get_width() const {
  return width;
}

template <class Type> size_t Matrix<Type>::get_height() const{
  return height;
}
}
#endif
