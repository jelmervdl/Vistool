#include "dataset.h"

using namespace std;
using namespace boost::filesystem;

string Dataset::getRoot(){
  return root;
}

vector<Category> Dataset::getCategories(){
  return categories;
}

void Dataset::addCategory(Category cat){
  categories.push_back(cat);
}

Dataset::Dataset(string str): root(str){
  path full_path =  system_complete(root);
  directory_iterator end_itr;
  if(is_directory(full_path)){
    try{
      for (directory_iterator itr( full_path ); itr != end_itr;++itr ){
	if(is_directory(itr->path())){
	  Category newcat((string) itr->path().filename().c_str(),
			  (string) itr->path().file_string().c_str());
	  for ( directory_iterator sitr(itr->path()); sitr != end_itr; ++sitr){
	    if(is_image((string)sitr->path().extension())){
	      DataPoint n (sitr->path().filename().c_str());
	      newcat.addDataPoint(n);
	    }
	  }  
	  Category newcat2 = newcat;
	  if(newcat.size() > 10){
	    addCategory(newcat);
	  }
	}
      }
    }
    catch(...){
    }
  } 
  mask.resize(categories.size());
}

void Dataset::setRoot(string str){
  root = str;
}

void Dataset::enableCategory(size_t i){
  mask.at(i) = 1;
}
void Dataset::enableCategory(string str){
  for(size_t i = 0; i < categories.size(); ++i)
    if(categories.at(i).getName().compare(str)==0)
      mask.at(i) = true;
}

void Dataset::print(){
  cout << "Database contains " << categories.size() << " classes" << endl << endl;
  cout << "Enabled Classes: " << endl;
  for(size_t i = 0; i < categories.size(); ++i)
    if(mask.at(i))
      cout << categories.at(i).getName() << endl;
  cout << endl;
}

void Dataset::train(){
  for(size_t i = 0; i < categories.size(); ++i)
    if(mask.at(i)){
      
    }
}
