#ifndef MULTITON_H
#define MULTITON_H

#include <string>
#include <map>

template<class Type>
class Multiton{
private:
  static std::map<std::string, Type*> instance_map;
  static std::map<std::string, bool> flag_map;
  static std::string current;
protected:
  Multiton(){
  }
public:
  static Type *getInstance(){
    return getInstance(current);
  }
  static Type *getInstance(std::string str){
    if(!flag_map[str]){
      flag_map[str] = true;
      instance_map[str] = new Type();
    }
    return instance_map[str];
  }
  static void select(std::string str){
    current = str;
  }

  static std::string get_current_name() {
    return current;
  }
};

template<class Type> std::map<std::string, Type*> Multiton<Type>::instance_map;
template<class Type> std::map<std::string, bool> Multiton<Type>::flag_map;
template<class Type> std::string Multiton<Type>::current;

#endif 

