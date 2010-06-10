#include "featureSelectionWindow.h"

using std::vector;
using std::stringstream;
using std::cout;
using std::endl;

namespace vito{
namespace gui{

FeatureSelectionWindow::FeatureSelectionWindow(){
  feature_panel = NULL;
  fill(); 
}

void FeatureSelectionWindow::fill(){
  if(feature_panel != NULL)
    feature_panel->close();
  feature_panel = GLUI_Master.create_glui("Feature Selection", 0, 800, 100);
  vector<features::Feature*> features = features::getExistingFeatures();
  Parameters *p = Parameters::getInstance();
  for(size_t i = 0; i < features.size(); i++){
    stringstream ss;
    ss << "feature_" << features[i]->getParameterName();
    cout << ss.str() << endl;
    feature_panel->add_checkbox( features[i]->getParameterName().c_str(),
				 &p->intParameters[ss.str().c_str()]);
  }
}

}}
