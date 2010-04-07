#include "gluiGL.h"

void setupOpenGL(){
  ToolState &state = *ToolState::getInstance();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, state.window_height, state.window_width, 0, 0, 1); // we want 2d projection mode! 
  glMatrixMode(GL_MODELVIEW); // bring us back to model mode 
  glDisable( GL_DEPTH_TEST); //2d, no depth 
  glDisable( GL_LIGHTING ); // 2d, no light 
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
}


void display(void){
  ToolState &state = *ToolState::getInstance();
  using namespace states;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  switch(state.dm){
  case Single_Image:
    if(state.current_single_image_texture!=NULL)
      state.current_single_image_texture->draw(state.window_height);
    break;
  case Show_Dataset:
    if(state.current_db != NULL){
      size_t grid = ceil(sqrt(state.ims_per_page));
      float scale = 1.0/grid;
      glScalef(scale, scale, 0);
      size_t count  = 0;
      glPushMatrix();
      for(vector<Texture *>::iterator it = state.textures.begin();
	  it != state.textures.end();
	  ++it){
	(*it)->draw(state.window_height);
	glTranslatef(800, 0, 0);
	count++;
	if(count == grid){
	  count = 0;
	  glPopMatrix();
	  glTranslatef(0, 800, 0);
	  glPushMatrix();
	}
      }
      glPopMatrix();
    }
    break;
  default:
    break;
  }
  glutSwapBuffers();
}

void myGlutIdle( void ){
  ToolState &state = *ToolState::getInstance();
  if ( glutGetWindow() != state.image_display_window )
    glutSetWindow(state.image_display_window);
  glutPostRedisplay();
  state.main_gui->sync_live();
}

void setupWindow(){
  ToolState &state = *ToolState::getInstance();
  glutInitWindowPosition( 0, 0 );
  state.window_height = 800;
  state.window_width = 800;
  glutInitWindowSize( state.window_width, state.window_height );
  state.image_display_window = glutCreateWindow( "Image Viewer" );
}
