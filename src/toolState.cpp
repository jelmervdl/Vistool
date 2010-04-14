#include "toolState.h"

namespace vito{
namespace gui{

ToolState::ToolState(){
  dm = states::Single_Image;
  ds = states:: Enabled_Datasets;
  display_modifier = states::No_Modifier;

  current_image_page = 0;
  enabled_classifier = states::NearestNeighbor;

  ims_per_page = 16;
}
}}
