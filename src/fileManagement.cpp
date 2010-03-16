#include "fileManagement.h"

using namespace boost::filesystem;
using namespace std;

bool is_image (boost::filesystem::path::string_type  string){
  if(string == ".png"){
    return true;
  }
  if(string == ".jpg"){
    return true;
  }
  return false;
}

/*
void createTrainAndTestSet(vector<Category> * cats, vector<DataPoint> * samples, float cut){
  size_t currentClass = 0;
  for(vector<Category>::iterator it = cats->begin(); it != cats->end(); ++it){
    vector<string> files = it->file_list();
    random_shuffle( files.begin(), files.end()); 
    size_t icut = (size_t) (cut * files.size());
    size_t count = 0;
    for(vector<string>::iterator it2 = files.begin(); it2 != files.end(); ++it2){
      if(count < icut){
	Sample s  = Sample(currentClass, *it2);
	samples->push_back(s);
      }else
	targets->push_back(*it2);
      count++;
    }
    currentClass++;
  }
}


void printDatabase(vector<Category> * db){
  cout << "Database contains " << db->size() << " classes, including:\n";
  for(vector<Category>::iterator it = db->begin(); 
      it!=db->end(); ++it){
    cout << "\t" << it->getName() << endl;
    vector<DataPoint> f = it->getDataPoints();
    for(vector<DataPoint>::iterator it2 = f.begin(); it2!=f.end(); ++it2)
      cout << "\t\t" << it2->getImageURL() << endl;
  }
}


bool isDataset(string dir, Dataset * classes){
  path full_path =  system_complete(dir);
  directory_iterator end_itr;
  if(is_directory(full_path)){
    classes->setRoot(dir);
    try{
      for ( directory_iterator itr( full_path ); itr != end_itr;++itr ){
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
	    classes->addCategory(newcat);
	  }
	}
      }
    }
    catch(...){
    }
  for(vector<Category>::iterator it = classes->begin(); 
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
*/
