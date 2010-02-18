#ifndef SINGLETON_H
#define SINGLETON_H

template<class T> 
class Singleton{
 private:
  static bool instanceFlag;
  static T * singleton;
 protected:
  Singleton(){
  };
 public:
  static T * getInstance(){
    if(!instanceFlag){
      singleton = new T();
      instanceFlag = true;
    }
    return singleton;
  };
  ~Singleton(){
  };
}; 

template <class T> T* Singleton<T>::singleton = 0;
template <class T> bool Singleton<T>::instanceFlag = false;

#endif


