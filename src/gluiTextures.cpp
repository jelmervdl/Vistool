#include "gluiTextures.h"

using Magick::Image;
using VisionToolCore::Matrix;
using VisionToolFeatures::SiftDescriptor;
using VisionToolFeatures::Histogram;
using VisionToolFeatures::Feature;
using VisionToolFeatures::Gradient;
using VisionToolFeatures::imageGradient;

namespace VisionToolGUI{

void refreshTexture(size_t p){
  ToolState &state = *ToolState::getInstance();
  for(size_t i = 0; i < state.textures.size(); ++i)
    delete state.textures[i];
  state.textures.clear();
  // display images.
  if(state.display_modifier == states::No_Modifier)
    for(size_t i = p; i < (size_t) state.ims_per_page + p && 
	  i < (size_t) state.currently_view_datapoints.size() ; ++i){
      printf("here's a file called \n");//,  currently_view_datapoints.at(i)->get_file_name());
      state.textures.push_back(  new Texture (state.currently_view_datapoints.at(i), 
					      state.image_display_window));
    }
  // display their gradients
  if(state.display_modifier == states::Show_Gradient)
    for(size_t i = p; i < (size_t) state.ims_per_page + p && i < (size_t) state.currently_view_datapoints.size() ; ++i){
      MyImage im (state.currently_view_datapoints.at(i)->get_image_url());
      Matrix<float> gray_image = im.getGrayscaleMatrix();
      Matrix<Gradient> image_gradient = imageGradient(gray_image);
      state.textures.push_back( new Texture(&image_gradient, 
					    state.image_display_window));
    }
  //display sift
  if(state.display_modifier == states::Show_Sift)
    for(size_t i = p; i < (size_t) state.ims_per_page + p && 
	  i < (size_t) state.currently_view_datapoints.size(); ++i){
      MyImage im (state.currently_view_datapoints.at(i)->get_image_url());
      SiftDescriptor s;
      Image canvas;
      s.extract(&im, true, &canvas);
      state.textures.push_back(new Texture(&canvas, state.image_display_window));
    }
  //display histpgra,s
  display();
}

}
