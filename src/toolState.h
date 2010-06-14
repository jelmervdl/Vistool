#ifndef TOOLSTATE_H
#define TOOLSTATE_H

#include "singleton.h"
#include "core.h"
#include "dataset.h"
#include "parameterPanel.h"
#include "texture.h"
#include "classifier.h"
#include "evaluation.h"

namespace vito{
namespace gui{

using evaluation::Evaluation;

class ToolState:  public Singleton<ToolState>{
 public:
  //Pointers
  GLUI_Listbox               *selected_class_listbox;
  classification::Classifier *current_classifier;
  ParameterPanel             *parameter_panel;
  DataPoint *singleDp;
  Texture *current_single_image_texture;

  states::DisplayMode      dm;
  states::DatasetOnDisplay ds;
  states::DisplayModifier display_modifier;

  Dataset                     current_db;
  size_t                      current_image_page;
  std::vector <Texture>       textures;
  std::vector <DataPoint*>    currently_view_datapoints; 
  std::vector <DataPoint>     train_data, test_data;
  std::vector <int>           test_result;
  int                         enabled_classifier;
  int                         enabled_feature;

  // class view selection
  int                         selected_class;
  Evaluation                  current_evaluation;
  std::vector<int>            current_classes;

  //Global Glui Objects 
  GLUI_StaticText *busytxt;
  GLUI *main_gui;
  GLUI *classes;
  GLUI *stats;
  GLUI_Listbox *image_mod;
  int ims_per_page;

  // main window
  size_t window_width;
  size_t window_height;
  int    image_display_window;
  int one_class_target;
  
  // Single Image parameters
  size_t image_width; 
  size_t image_height;
  ToolState();
};

}}
#endif
