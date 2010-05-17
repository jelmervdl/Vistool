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
    delete singleton;
    singleton = 0;
    instanceFlag = false;
  };
}; 

template <class T> T* Singleton<T>::singleton;
template <class T> bool Singleton<T>::instanceFlag;

#endif


