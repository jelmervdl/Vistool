#include "gluiFeatures.h"

using VisionToolFeatures::FeatureExtractor;

namespace VisionToolGUI{

void extractFeatures(){
  ToolState &state = *ToolState::getInstance();
  state.busytxt->set_text("extracting...");
  glutPostRedisplay();
  FeatureExtractor * f = FeatureExtractor::getInstance();
  f->saveDescriptorsToFile(state.current_db);
  state.busytxt->set_text("done");
}

}
