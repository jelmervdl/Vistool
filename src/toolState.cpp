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
  parameter_panel = 0;
  current_db = 0;
  current_classifier = 0;
  current_evaluation = 0;
  selected_class_listbox = 0;
  main_gui = 0;
  classes = 0;
  stats = 0;
  current_single_image_texture = 0;
  singleDp = 0;
}
}}
