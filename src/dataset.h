#ifndef DATASET_H
#define DATASET_H

#include <map>
#include "core.h"
#include "category.h"
#include "fileManagement.h"
#include "singleton.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>


namespace vito{

std::vector<DataPoint> getDataPoints(boost::filesystem::path p,
				     size_t label = 0,
				     std::string = "");

struct DatasetSpecification{
  std::string name;
  std::string root;
  std::vector<std::string> categories;
};

class Specifications : public Singleton<Specifications>{
private:
  std::map<std::string, DatasetSpecification> readDatasetIndex(std::string str);
public:
  Specifications() :
    datasets(readDatasetIndex("datasets/index.xml")){}
  
  typedef std::map<std::string, DatasetSpecification> const SpecificationMap;
  SpecificationMap datasets;
};



class Dataset{
 private:
  static std::string prefdset;
  std::map<size_t, std::string> category_names;
  std::vector<Category> categories;
  std::string root;

 protected:
  size_t                  smallestCategorySize();

 public:
  //constructor:
  Dataset();
  Dataset(std::string rt);

  // getters:
  std::vector<Category>  *getCategories();
  std::vector<Category*>  getEnabled();

  std::string             getCatName(size_t cat) ;
  std::string             get_root() const ;

  //setters

  void                    setRoot(std::string str);
  void                    addCategory(Category cat);
  void                    enableCategory(size_t i);
  void                    enableCategory(std::string str);
  void                    disableCategory(size_t i);
  void                    disableCategory(std::string str);
  void                    enableRandom(const int number);
  void                    disableAll();
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
					  size_t max_points_per_category = 0);
  static Dataset          createDatasetByName(std::string str);
  static Dataset          createDatasetBySpecification(DatasetSpecification dss);
  static Dataset          getPrefferedDataset();
  static std::string      getPrefferedDatasetName();
  static void             setPrefferedDataset(std::string str);
  static bool prefferredExtracted;
};
}

#endif
