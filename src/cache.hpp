#ifndef CACHE_HPP
#define CACHE_HPP

#include <map>
#include <string>
#include <stdexcept>

template <class T>
class Cache
{
public:
  typedef T value_type;
  void add(std::string const &key, value_type const &item);
  bool contains(std::string const &key) const;
  T const &get(std::string const &key) const;

private:
  typedef std::map<std::string, value_type> index;
  index d_items;
};

template <class T>
bool Cache<T>::contains(std::string const &key) const
{
  return d_items.find(key) != d_items.end();
}

template <class T>
void Cache<T>::add(std::string const &key, value_type const &item)
{
  d_items[key] = item;
}

template <class T>
T const &Cache<T>::get(std::string const &key) const
{
  typename index::const_iterator pos(d_items.find(key));

  if (pos == d_items.end())
    throw std::out_of_range("Cache does not contain specific key: " + key);
  
  return pos->second;
}

#endif