#ifndef SAMPLE_H
#define SAMPLE_H

#include <string>

using namespace std;

class Sample{
 private:
  size_t sample_class;
  string location;
 public:
  Sample(size_t cl, string loc);
  string getLocation();
  size_t getClass();
};

#endif
