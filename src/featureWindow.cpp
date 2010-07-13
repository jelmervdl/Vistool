#include "featureWindow.h"

using std::vector;

namespace vito{

using features::Feature;
using features::getExistingFeatures;

namespace gui{

FeatureWindow::FeatureWindow(){
  window = GLUI_Master.create_glui( "FeatureSelection", 0, 800, 0 );
  vector<Feature*> features = getExistingFeatures();
  typedef vector<Feature*>::iterator feat_iter;
  for(feat_iter it = features.begin(); it != features.end(); ++it){
    Feature &cur_feat = **it;
    window->add_checkbox( cur_feat.getParameterName().c_str(),
			  0, 1, (GLUI_Update_CB) NULL);
  } 
}

GLUI *FeatureWindow::getWindowPointer(){
  return window;
}


}}
