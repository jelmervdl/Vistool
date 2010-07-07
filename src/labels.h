#ifndef LABELS_H
#define LABELS_H

#include <vector>

namespace vito{

typedef int Label;

class LabelCollection : public std::vector<Label>{
public:
  LabelCollection() : std::vector<Label>(){}
  LabelCollection(size_t s) : std::vector<Label>(s){}
};

}


#endif 
