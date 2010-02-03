#include "fileManagement.h"

using namespace boost::filesystem;
using namespace std;

void printDatabase(list<Category> * db){
  cout << "Database contains " << db->size() << " classes, including:\n";
  for(list<Category>::iterator it = db->begin(); 
      it!=db->end(); ++it){
    cout << "\t" << it->getName() << endl;
    list<string> f = it->file_list();
    for(list<string>::iterator it2 = f.begin(); it2!=f.end(); ++it2)
      cout << "\t\t" << *it2 << endl;
  }
}

bool isDataset(string dir, list<Category> * classes){
  path full_path =  system_complete(dir);
  directory_iterator end_itr;
  if(is_directory(full_path)){
    try{
      for ( directory_iterator itr( full_path ); itr != end_itr;++itr ){
	if(is_directory(itr->path())){
	  Category newcat((string) itr->path().filename().c_str());
	  for ( directory_iterator sitr(itr->path()); sitr != end_itr; ++sitr){
	    if(is_image((string)sitr->path().extension())){
	      newcat.add_file(sitr->path().file_string().c_str());
	    }
	  }  
	  Category newcat2 = newcat;
	  if(newcat.size() > 10){
	    classes->push_back(newcat);
	  }
	}
      }
    }
    catch(...){
    }
  for(list<Category>::iterator it = classes->begin(); 
	  it!=classes->end(); 
	  ++it){
      }
  }
  else{
    cout << full_path << " is not a directory\n";
    return 0;
  }
  if(classes->size() > 1)
    return 1;
  else
    return 0;
}

bool is_image (boost::filesystem::path::string_type  string){
  if(string == ".png"){
    return true;
  }
  if(string == ".jpg"){
    return true;
  }
  return false;
}

Category::Category(string give_name){
    name = give_name;
}

list <string> Category::file_list(){
  return files;
}

string Category::getName(){
  return name;
}

void Category::add_file(string file){
  files.push_back(file);
}
size_t Category::size(){
  return files.size();
}
