#ifndef DATASET_H
#define DATASET_H

#include <map>
#include "core.h"
#include "category.h"
#include "fileManagement.h"

namespace vito{


class Dataset{
 private:
  std::map<size_t, std::string> category_names;
  std::vector<Category> categories;
  std::string root;

 public:
  //constructor:
  Dataset();
  Dataset(std::string rt);

  // getters:
  std::vector<Category>  *getCategories();
  std::vector<Category*>  getEnabled();

  std::string             getCatName(size_t cat) ;
  std::string             get_root() const ;
  size_t                  smallestCategory() ;

  //setters

  void                    setRoot(std::string str);
  void                    addCategory(Category cat);
  void                    enableCategory(size_t i);
  void                    enableCategory(std::string str);
  void                    disableCategory(size_t i);
  void                    disableCategory(std::string str);
  void                    enableRandom(const int number);
  void                    print();
  void                    shuffle();
  std::vector<Dataset>         split(float ratio = 0.5);
  void                    cut(float ratio, bool second);

  DataPointCollection     enabledPoints(bool eqrep = true) ;
  std::vector<DataPoint*> enabledDataPoints(bool eqrep= true);

  void                    randomDataSplit(std::vector<DataPoint> * train, 
					  std::vector<DataPoint> * test, 
					  float cut = 0.5, 
					  bool eqrep = true,
					  int max = -1);
};
}

#endif
