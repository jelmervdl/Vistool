#include "fileManagement.h"

using namespace boost::filesystem;
using namespace std;

namespace vito{

/* appearantly I had more in mind for this file than this... */

bool is_image (boost::filesystem::path::string_type  string){
  if(string == ".png"){
    return true;
  }
  if(string == ".jpg"){
    return true;
  }
  return false;
}

}
