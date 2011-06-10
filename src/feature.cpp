#include "feature.h"

using Magick::Image;
using std::vector;
using std::string;
using std::cout;
using std::endl;

namespace vito{
namespace features{

Feature::~Feature(){
}

Feature::Feature(){
}

bool Feature::isActive(){
  stringstream ss;
  ss << "feature_" << getParameterName();
  return Parameters::getInstance()->getiParameter(ss.str()) > 0;
}

vector<float> Feature::extract(MyImage *image, bool saveVisualRepresentation, string vis_rep_loc){
  if(saveVisualRepresentation){
    Image newImage;
    vector<float> result = extract_(image, saveVisualRepresentation, &newImage);
    newImage.write(vis_rep_loc);
    return result;
  }else
    return extract_(image, false, NULL);
}

void Feature::extractTo(vector<float> * vec, MyImage * im){
  vector<float> extr = extract_(im, false, NULL);
  vec->insert(vec->end(), extr.begin(), extr.end()); 
}

bool Feature::isStack(){
  return false;
}

}}
