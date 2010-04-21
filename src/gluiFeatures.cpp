#include "gluiFeatures.h"

namespace vito{
namespace gui{

using features::FeatureExtractor;
 
void recalculateFeatures(){
  ToolState &state = *ToolState::getInstance();
  glutPostRedisplay();
  FeatureExtractor * f = FeatureExtractor::getInstance();
  f->saveDescriptorsToFile(state.current_db, true);
}

void extractFeatures(){
  ToolState &state = *ToolState::getInstance();
  glutPostRedisplay();
  FeatureExtractor * f = FeatureExtractor::getInstance();
  f->saveDescriptorsToFile(state.current_db);
}

}}
