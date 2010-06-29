#ifndef MULTITON_H
#define MULTITON_H

#include <vector>
#include <string>
#include <map>

template<class Type>
class Multiton{
private:
  static std::string current_name;
  static Type *current;
  static std::map<std::string, Type*> instance_map;
  static std::map<std::string, bool> flag_map;
  static std::vector<Type*> unique_instances;
protected:
  Multiton(){
    current = getInstance("");
  }
public:
  static int getUnique(){
    Type *new_type = new Type();
    unique_instances.push_back(new_type);
    return unique_instances.size() - 1;
  }

  static void setUnique(int i){
    current = unique_instances[i];
  }

  static Type *getInstance(){
    return current;
  }
  static Type *getInstance(std::string str){
    if(!flag_map[str]){
      flag_map[str] = true;
      instance_map[str] = new Type();
    }
    return instance_map[str];
  }
  static void select(std::string str){
    current = instance_map[str];
    current_name = str;
  }
  static std::string get_current_name() {
    return current_name;
  }
};

template<class Type> std::map<std::string, Type*> Multiton<Type>::instance_map;
template<class Type> std::map<std::string, bool> Multiton<Type>::flag_map;
template<class Type> std::string Multiton<Type>::current_name;
template<class Type> Type* Multiton<Type>::current;
template<class Type> std::vector<Type*> Multiton<Type>::unique_instances;


#endif 

