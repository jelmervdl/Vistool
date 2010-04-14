#include "gluiFeatures.h"

namespace vito{
namespace gui{

using features::FeatureExtractor;

void extractFeatures(){
  ToolState &state = *ToolState::getInstance();
  state.busytxt->set_text("extracting...");
  glutPostRedisplay();
  FeatureExtractor * f = FeatureExtractor::getInstance();
  f->saveDescriptorsToFile(state.current_db);
  state.busytxt->set_text("done");
}

}}
