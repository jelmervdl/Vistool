#ifndef TOOLSTATE_H
#define TOOLSTATE_H

#include "singleton.h"
#include "core.h"
#include "dataset.h"
#include "parameterPanel.h"
#include "texture.h"
#include "classifier.h"

struct tool_state{
  states::DisplayMode      dm;
  states::DatasetOnDisplay ds;
  states::DisplayModifier display_modifier;

  ParameterPanel *    parameter_panel;
  Dataset *           current_db;
  size_t              current_image_page;
  std::vector <Texture *>    textures;
  std::vector <DataPoint*> currently_view_datapoints; 
  std::vector <DataPoint>  train_data, test_data;
  std::vector <int>        test_result;
  Classifier *        current_classifier;
  states::EnabledClassifier   enabled_classifier;

  // class view selection
  int            selected_class;
  Evaluation *   current_evaluation;
  GLUI_Listbox * selected_class_listbox;
  std::vector<int>    current_classes;

  //Global Glui Objects 
  GLUI_StaticText * busytxt;
  GLUI *            main_gui;
  GLUI *            classes;
  GLUI *            stats;
  int               ims_per_page;

  // main window
  size_t window_width;
  size_t window_height;
  int    image_display_window;
  
  // Single Image parameters
  Texture * current_single_image_texture;
  size_t image_width; 
  size_t image_height;
  DataPoint * singleDp;
  
};

class ToolState: public tool_state, public Singleton<ToolState>{
 public:
  ToolState();
};
#endif
