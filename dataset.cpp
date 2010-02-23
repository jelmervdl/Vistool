#include "dataset.h"

using namespace std;
using namespace boost::filesystem;

string Dataset::getRoot(){
  return root;
}

vector<Category> * Dataset::getCategories(){
  return &categories;
}

void Dataset::addCategory(Category cat){
  categories.push_back(cat);
}

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
	  for ( directory_iterator sitr(itr->path()); sitr != end_itr; ++sitr){
	    if(is_image((string)sitr->path().extension())){
	      string filename = (string) sitr->path().filename().c_str();
	      string fileurl = (string) sitr->path().file_string().c_str();
	      string descriptor = DESCRIPTOR_LOCATION+catname+"/"+filename+".desc";
	      DataPoint n (label, filename, fileurl, descriptor);
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
  *categories.at(i).getEnabled() = 1;
}
void Dataset::enableCategory(string str){
  for(size_t i = 0; i < categories.size(); ++i)
    if(categories.at(i).getName().compare(str)==0)
      *categories.at(i).getEnabled() = true;
}

void Dataset::print(){
  cout << "Database contains " << categories.size() << " classes" << endl << endl;
  cout << "Enabled Classes: " << endl;
  for(size_t i = 0; i < categories.size(); ++i)
    if(*categories.at(i).getEnabled())
      cout << categories.at(i).getName() << endl;
  cout << endl;
}

vector<Category> Dataset::getEnabled(){
  vector<Category> enabled;
  for(size_t i = 0; i < categories.size(); ++i)
    if(*categories.at(i).getEnabled())
      enabled.push_back(categories.at(i));
  return enabled;
}

void Dataset::rSplit(vector<DataPoint> * train, vector<DataPoint> * test, 
		     float cut, bool eqrep){
  vector<Category> enabled = getEnabled();
  size_t min = 0;
  if(eqrep)
    for(vector<Category>::iterator cat = enabled.begin();
	cat != enabled.end(); ++cat)
      if(min > cat->getDataPoints()->size() || min == 0)
	min = cat->getDataPoints()->size();
  for(vector<Category>::iterator cat = enabled.begin();
      cat != enabled.end(); ++cat){
    vector<DataPoint> * dps = cat->getDataPoints();
    random_shuffle(dps->begin(), dps->end());
    if(eqrep) {
      dps = new vector<DataPoint>(dps->begin(), dps->begin() + min);
    }
    size_t int_cut = cut * dps->size();
    for(size_t i = 0; i < int_cut; ++i)
      train->push_back(dps->at(i));
    for(size_t i = (size_t) int_cut; i < dps->size(); ++i)
      test->push_back(dps->at(i));
    if(eqrep)
      delete dps;
  }
}


