#include "dataset.h"

using namespace std;
using namespace boost::filesystem;

namespace vito{

string Dataset::get_root() const {
  return root;
}

vector<Category> * Dataset::getCategories(){
  return &categories;
}

void Dataset::addCategory(Category cat){
  categories.push_back(cat);
}

Dataset::Dataset(){
};

Dataset::Dataset(string str): root(str){
  path full_path =  system_complete(root);
  directory_iterator end_itr;
  size_t label = 0;
  if(is_directory(full_path)){
    try{
      for (directory_iterator itr( full_path ); itr != end_itr;++itr ){
	if(is_directory(itr->path())){
	  string root, descriptor, catname;
	  root = (string) itr->path().file_string().c_str();
	  catname = (string) itr->path().filename().c_str();
	  Category newcat(catname, root, label);
	  category_names[label] = catname;
	  for ( directory_iterator sitr(itr->path()); sitr != end_itr; ++sitr){
	    if(is_image((string)sitr->path().extension())){
	      string filename = (string) sitr->path().filename().c_str();
	      string fileurl = (string) sitr->path().file_string().c_str();
	      DataPoint n (label, filename, fileurl, catname);
	      newcat.addDataPoint(n);
	    }
	  }  
	  Category newcat2 = newcat;
	  if(newcat.size() > 10){
	    addCategory(newcat);
	    label++;
	  }
	}
      }
    }
    catch(...){
    }
  } 
}

void Dataset::setRoot(string str){
  root = str;
}

void Dataset::enableCategory(size_t i){
  *categories.at(i).enabledLiveVar() = 1;
}
void Dataset::enableCategory(string str){
  for(size_t i = 0; i < categories.size(); ++i)
    if(categories.at(i).get_name().compare(str)==0)
      *categories.at(i).enabledLiveVar() = true;
}

void Dataset::disableCategory(size_t i){
  *categories.at(i).enabledLiveVar() = 0;
}

void Dataset::disableCategory(std::string str){
  for(size_t i = 0; i < categories.size(); ++i)
    if(categories.at(i).get_name().compare(str)==0)
      *categories.at(i).enabledLiveVar() = 0;
}

void Dataset::print(){
  cout << "Database contains " << categories.size() 
       << " classes" << endl << endl
       << "Enabled Classes: " << endl;
  for(size_t i = 0; i < categories.size(); ++i)
    if(*categories.at(i).enabledLiveVar())
      cout << categories.at(i).get_name() << endl;
  cout << endl;
}

vector<Category*> Dataset::getEnabled(){
  vector<Category*> enabled;
  for(size_t i = 0; i < categories.size(); ++i)
    if(*categories.at(i).enabledLiveVar())
      enabled.push_back(&categories.at(i));
  return enabled;
}

size_t Dataset::smallestCategory(){
  vector<Category*> enabled = getEnabled();
  size_t min = 0;
  for(vector<Category*>::iterator cat = enabled.begin();
      cat != enabled.end(); ++cat)
    if(min > (*cat)->get_data_points()->size() || min == 0)
      min = (*cat)->get_data_points()->size();
  return min;
}


void Dataset::randomDataSplit(vector<DataPoint> * train, 
			      vector<DataPoint> * test, 
			      float cut, 
			      bool eqrep,
			      int max){
  vector<Category*> enabled = getEnabled();
  size_t min = 0;
  if(eqrep)
    min = smallestCategory();
  for(vector<Category*>::iterator cat = enabled.begin();
      cat != enabled.end(); ++cat){
    // extract points for this category
    vector<DataPoint> dps = (*cat)->get_data_points_();
    random_shuffle(dps.begin(), dps.end());
    if(eqrep) {
      dps = vector<DataPoint>(dps.begin(), dps.begin() + min);
    }
    if(max > (int) dps.size() || max == -1) max = dps.size();
    int int_cut;
    max < 0? int_cut = cut * dps.size() : int_cut = cut * max;
    //extract training points
    for(int i = 0; i < int_cut && i < max ; ++i){
      train->push_back(dps.at(i));
    }
    //extract test points
    for(int i = int_cut; i < (int) dps.size() && i < max; ++i){
      test->push_back(dps.at(i));
    }
  }
  cout << "random data split:" << endl 
       << "  enabled Categories: " << enabled.size() << endl
       << "  train: " << train->size() << endl
       << "   test: " << test->size() << endl;
}

vector<DataPoint*> Dataset::enabledDataPoints(bool eqrep){
  size_t min = smallestCategory();
  vector<Category*> enabled = getEnabled();
  vector<DataPoint*> result;
  for(size_t i = 0; i < enabled.size(); ++ i){
    Category * ccat = enabled[i];
    vector<DataPoint*> dps = ptr::ptrDeMorgan(ccat->get_data_points());  
    random_shuffle(dps.begin(), dps.end());
    size_t max = min;
    if(!eqrep)
      max = dps.size();
    for(size_t j = 0; j < max; ++j)
      result.push_back(dps[j]);
  }
  return result;
}

DataPointCollection Dataset::enabledPoints(bool eqrep) {
  int min = smallestCategory();
  vector<Category*> enabled_categories = getEnabled();
  DataPointCollection result;
  for(size_t i = 0; i < enabled_categories.size(); ++i){
    vector<DataPoint> * data_points = enabled_categories[i]->get_data_points();
    if(!eqrep){
      random_shuffle(data_points->begin(), data_points->end());
      result.insert(result.end(), data_points->begin(), data_points->end());
    }else{
      result.insert(result.end(), data_points->begin(), data_points->begin() + min);
    }
  }
  return result;
}

string Dataset::getCatName(size_t cat) {
  return category_names[cat];
}

void Dataset::enableRandom(const int number){
  vector<int> enabled(categories.size());
  for(size_t i = 0; (int) i < number && i < enabled.size(); ++i)
    enabled[i] = 1;
  random_shuffle(enabled.begin(), enabled.end());
  for(size_t i = 0; i < categories.size(); ++i)
    *categories[i].enabledLiveVar() =  enabled[i];
}

vector<Dataset> Dataset::split(float ratio){
  shuffle();
  assert(ratio < 1 && ratio > 0);
  vector<Dataset> datasets;
  datasets.push_back(*this);
  datasets.push_back(*this);
  datasets[0].cut(ratio, false);
  datasets[0].cut(ratio, true);
  return datasets;
}

void Dataset::cut(float ratio, bool second){
  for(vector<Category>::iterator it = categories.begin();
      it != categories.end();
      ++it){
    size_t cut = ratio * it->size();
    vector<DataPoint> &dps = *it->get_data_points();
    if(!second) dps.erase(dps.begin(), dps.begin() + cut - 1);
    else dps.erase(dps.begin() + cut, dps.end());
  }
}

void Dataset::shuffle(){
  for(vector<Category>::iterator it = categories.begin();
      it != categories.end();
      ++it)
    it->shuffle();
}
}

