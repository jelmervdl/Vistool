#include "gluiView.h"

using std::vector;

void viewDataset(){
  ToolState &state = *ToolState::getInstance();
  if(state.current_db != NULL){
    state.dm = states::Show_Dataset;
    setViewSelection();
    refreshTexture(); 
    display();
  }
  state.current_image_page = 0;
}

void setViewSelection(){
  ToolState &state = *ToolState::getInstance();
  state.currently_view_datapoints.clear();

  using namespace states;
  if(state.ds == Enabled_Datasets){
      vector<Category*> enabs = state.current_db->getEnabled();
      for(vector<Category*>::iterator cat = enabs.begin(); cat != enabs.end(); ++cat){
	vector<DataPoint> * dps = (*cat)->getDataPoints();
	for(size_t i = 0; i < dps->size(); ++i){
	  state.currently_view_datapoints.push_back(&dps->at(i));
	}
      }
  }
  if(state.ds == Training_DataPoints){
    state.currently_view_datapoints = VisionCore::ptrDeMorgan<DataPoint>(&state.train_data);
  }

  if(state.ds == Testing_DataPoints){
    state.currently_view_datapoints = VisionCore::ptrDeMorgan<DataPoint>(&state.test_data);
  }
  if(state.ds == Particular_Category){
    state.current_evaluation->print();
    state.currently_view_datapoints.clear();
    if(state.current_evaluation != NULL){
      state.currently_view_datapoints = state.current_evaluation->getInstancesClassifiedAs(state.selected_class);
    }
  }
  state.image_width  = state.window_width / state.ims_per_page;
  state.image_height = state.window_height / state.ims_per_page;
  refreshTexture();
}
