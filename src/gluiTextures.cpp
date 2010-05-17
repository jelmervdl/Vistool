#include "gluiTextures.h"

using Magick::Image;

namespace vito{
namespace gui{

using features::SiftDescriptor;
using features::Histogram;
using features::Feature;
using features::Gradient;
using features::imageGradient;


void refreshTexture(size_t p){
  ToolState &state = *ToolState::getInstance();
  for(int i = 0; i < (int) state.textures.size(); ++i){
    state.textures[i].destroyTexture();
  }
  state.textures.clear();

  // display images.
  if(state.display_modifier == states::No_Modifier){
    for(size_t i = p; i < (size_t) state.ims_per_page + p && 
	  i < (size_t) state.currently_view_datapoints.size() ; ++i){
      state.textures.push_back( Texture (state.currently_view_datapoints.at(i), 
					 state.image_display_window));
    }
  }
  // display their gradients
  if(state.display_modifier == states::Show_Gradient)
    for(size_t i = p; i < (size_t) state.ims_per_page + p && i < (size_t) state.currently_view_datapoints.size() ; ++i){
      MyImage im (state.currently_view_datapoints.at(i)->get_image_url());
      Matrix<float> gray_image = im.getGrayscaleMatrix();
      Matrix<Gradient> image_gradient = imageGradient(gray_image);
      state.textures.push_back( Texture(&image_gradient, 
					state.image_display_window));
    }
  //display sift
  if(state.display_modifier == states::Show_Sift)
    for(size_t i = p; i < (size_t) state.ims_per_page + p && 
	  i < (size_t) state.currently_view_datapoints.size(); ++i){
      MyImage im (state.currently_view_datapoints.at(i)->get_image_url());
      SiftDescriptor s;
      Image canvas;
      s.extract_(&im, true, &canvas);
      state.textures.push_back(Texture(&canvas, state.image_display_window));
    }
  //display histpgrams
  display();
}

}}
