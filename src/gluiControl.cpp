#include "gluiControl.h"

using vito::classification::getExistingClassifiers;
using vito::classification::Classifier;

namespace vito{
namespace gui{

void initGlui(){
  ToolState &state = *ToolState::getInstance();
  state.parameter_panel = new ParameterPanel();
  state.main_gui = GLUI_Master.create_glui( "Control", 0, 800, 0 );
  state.busytxt = state.main_gui->add_statictext( "waiting" ); 

  GLUI_Panel * load_panel = state.main_gui->add_panel("load");
  state.main_gui->add_button_to_panel(load_panel, "Quit", 0,(GLUI_Update_CB)exit );
  state.main_gui->add_button_to_panel(load_panel, "Load Picture", 0, (GLUI_Update_CB)loadPicture );
  state.main_gui->add_button_to_panel(load_panel, "Load Dataset", 0, (GLUI_Update_CB)askDataset );
  state.main_gui->add_button_to_panel(load_panel, "Load Caltech", 0, (GLUI_Update_CB)loadCaltech );
  state.main_gui->add_column(false);

  GLUI_Panel * view_panel = state.main_gui->add_panel("view");
  state.main_gui->add_button_to_panel(view_panel, "Refresh", 0, (GLUI_Update_CB)viewDataset );
  state.main_gui->add_statictext_to_panel(view_panel, "Images Per Page:" ); 
  state.main_gui->add_spinner_to_panel(view_panel, "", GLUI_SPINNER_INT, &state.ims_per_page);
  state.main_gui->add_button_to_panel(view_panel, "Next Page", 0, (GLUI_Update_CB)nextPage );

  GLUI_Listbox * image_mod = state.main_gui->add_listbox_to_panel(view_panel, "show:", (int*) &state.display_modifier);
  image_mod->add_item(states::No_Modifier, "image");
  image_mod->add_item(states::Show_Gradient, "gradient");
  image_mod->add_item(states::Show_Sift, "sift");
  GLUI_Listbox * aap = state.main_gui->add_listbox_to_panel(view_panel, "view:", (int*) &state.ds, 0, 
					 (GLUI_Update_CB)viewDataset);
  aap->add_item(states::Enabled_Datasets, "Enabled");
  aap->add_item(states::Training_DataPoints, "Training Set");
  aap->add_item(states::Testing_DataPoints, "Test set");
  aap->add_item(states::Correct, "Correct");
  aap->add_item(states::Incorrect, "Incorr.");
  aap->add_item(states::Particular_Category, "Sel. Cat.");

  state.selected_class_listbox = state.main_gui->add_listbox_to_panel(view_panel, "part. class:", &state.selected_class, 0, (GLUI_Update_CB)selectAndShow);
  state.main_gui->add_column(false);
  GLUI_Panel * ml_panel = state.main_gui->add_panel("ML");
  state.main_gui->add_button_to_panel(ml_panel, "Get Descriptors", 0, (GLUI_Update_CB)extractFeatures );
  state.main_gui->add_button_to_panel(ml_panel, "Recalc Descr.", 0, (GLUI_Update_CB)recalculateFeatures );
  state.main_gui->add_button_to_panel(ml_panel, "Divide/Evaluate", 0, (GLUI_Update_CB)evaluateClassifier);
  state.main_gui->add_button_to_panel(ml_panel, "Cross-Validate", 0, (GLUI_Update_CB)crossValidate);
  state.main_gui->add_button_to_panel(ml_panel, "Classify", 0, (GLUI_Update_CB) non_set_classify);
  createClassifierSelectButton();
  //main_gui->add_button_to_panel(ml_panel, "Classify", 0, (GLUI_Update_CB)classify);
  state.main_gui->set_main_gfx_window(state.image_display_window);
  GLUI_Master.set_glutIdleFunc( myGlutIdle );
}

void nextPage(){
  ToolState &state = *ToolState::getInstance();
  state.current_image_page += state.ims_per_page;
  if(state.current_image_page > state.currently_view_datapoints.size())
    state.current_image_page = 0;
  refreshTexture(state.current_image_page);
  display();
}

void selectAndShow(){
  ToolState &state = *ToolState::getInstance();
  state.ds = states::Particular_Category;
  viewDataset();
}

void createClassifierSelectButton(){
  ToolState &state = *ToolState::getInstance();
  GLUI_Listbox * classif_sel = 
    state.main_gui->add_listbox("classif.:", (int*) &state.enabled_classifier);
  vector<Classifier*> classifier = getExistingClassifiers();
  for(int i = 0; i < classifier.size(); ++i){
    classif_sel->add_item(i, classifier[i]->get_name().c_str());  
  }
  while(classifier.size() > 0){  
    delete classifier.back();
    classifier.pop_back();
  }
  
}

}}
