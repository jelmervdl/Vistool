#include "gluiLoad.h"

using std::string;
using std::vector;

void loadDataset(string location){
  ToolState &state = *ToolState::getInstance();
  if(state.classes != 0)
    state.classes->close();
  state.classes = GLUI_Master.create_glui( "classes", 0, 800, 250 );
  delete state.current_db;
  state.current_db = new Dataset(location);
  vector<Category> * cats = state.current_db->getCategories();
  size_t c = 0;
  //  classes->add_column(true);
  GLUI_Panel * pan = state.classes->add_panel("categories");
  if(state.current_db != NULL){
    for(size_t i = 0; i < cats->size(); ++i){
      state.classes->add_checkbox_to_panel( pan,
				      (const char *)cats->at(i).getName().c_str(),
				      cats->at(i).getEnabled(),
				      1, (GLUI_Update_CB) viewDataset);
      c++;
      if(c%34==0)
	state.classes->add_column_to_panel(pan, false);
    }
  }
}

void loadPicture(){
  ToolState &state = *ToolState::getInstance();
  state.dm = states::Single_Image;
  glutSetWindow(state.image_display_window);
  delete state.current_single_image_texture;
  delete state.singleDp;
  string url  = askFile();
  state.singleDp = new DataPoint(0, "", url, ""); 
  state.current_single_image_texture = new Texture(state.singleDp, state.image_display_window);
}

void loadCaltech(){
  loadDataset("/Users/mauricemulder/workspace/datasets/caltech101/");
}

void askDataset(){
  loadDataset(askFile());
}
