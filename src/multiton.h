#ifndef MULTITON_H
#define MULTITON_H

#include <vector>
#include <string>
#include <map>
#include <assert.h>

template<class Type>
class Multiton{
private:
  static std::string current_name;
  static Type *current;
  static std::vector<Type*> buffer;
  static std::map<std::string, Type*> instance_map;
  static std::map<std::string, bool> flag_map;
  static std::vector<Type*> unique_instances;
protected:
  Multiton() {
  }
public:

  static void pop(){
    assert(buffer.size() > 0);
    current = buffer.back();
    buffer.pop_back();
  }

  static void push(int i){
    buffer.push_back(current);
    setUnique(i);
  }

  static void push(std::string str){
    buffer.push_back(current);
    select(str);
  }

  static int getUniqueClone(){
    Type *new_type = new Type();
    *new_type = *getInstance();
    unique_instances.push_back(new_type);
    return unique_instances.size() - 1;
  }

  static int getUnique(){
    Type *new_type = new Type();
    unique_instances.push_back(new_type);
    return unique_instances.size() - 1;
  }

  static void setUnique(int i){
    current = unique_instances[i];
  }

  static Type *getInstance(){
    if(current == 0)
      current = getInstance("default");
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
template<class Type> Type* Multiton<Type>::current = 0;
template<class Type> std::vector<Type*> Multiton<Type>::unique_instances;
template<class Type> std::vector<Type*> Multiton<Type>::buffer;

#endif 

