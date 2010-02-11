#include "gluiVisionTool.h"

using namespace std;
GLUI *glui;
GLUI *classes;
GLuint ctext;
size_t ct_width;
size_t ct_height;
size_t window_width;
size_t window_height;
int main_window;
vector<Category> *currentdb;

void start(int argc, char **argv){
  glutInit(&argc, argv);
  printf("Starting up glut...\n");
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition( 50, 50 );
  window_height = 800;
  window_width = 800;
  glutInitWindowSize( window_width, window_height );
  main_window = glutCreateWindow( "Image Viewer" );
  glutDisplayFunc(display);
  glGenTextures(1, &ctext);
  initTextures();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, window_height, window_width, 0, 0, 1); // we want 2d projection mode!                                                                                       
  glMatrixMode(GL_MODELVIEW); // bring us back to model mode                                                                                          
  glDisable( GL_DEPTH_TEST); //2d, no depth                                                                                                           
  glDisable( GL_LIGHTING ); // 2d, no light  
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  display();
  initGlui();
  glutMainLoop();
}

void initGlui(){
  glui = GLUI_Master.create_glui( "Control", 0, 950, 50 );
  glui->add_statictext( "Vision Tool" ); 
  glui->add_button( "Quit", 0,(GLUI_Update_CB)exit );
  glui->add_button( "Load Picture", 0, (GLUI_Update_CB)loadPicture );
  glui->add_button( "Load Dataset", 0, (GLUI_Update_CB)loadDataset );
  glui->set_main_gfx_window(main_window);
  GLUI_Master.set_glutIdleFunc( myGlutIdle );
}

void loadDataset(){
  classes = GLUI_Master.create_glui( "classes", 0, 950, 250 );
  currentdb = new vector<Category>();
  size_t c = 0;
  int aap = 0;
  if(isDataset(askFile(),currentdb)){
    cout << "is dataset" << endl;
    for(vector<Category>::iterator it = currentdb->begin();it != currentdb->end(); ++it){
      classes->add_checkbox((const char *)it->getName().c_str(), &aap, 1, (GLUI_Update_CB) loadPicture);
      c++;
      if(c%10==0)
	classes->add_column(true);
    }
  }
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW); // bring us back to model mode                                                                                          
  glLoadIdentity();
  size_t height, width;
  if(ct_height > window_height){
    height = window_height;
    width = ct_width * (window_height / (double) ct_height);
  } else{
    height = ct_height;
    width = ct_width;
  }
  if (width > window_width){
    height = window_width * (height / width);
    width = window_width;
  }
  drawTexture(ctext, width, height );
  glutSwapBuffers();
}

void initTextures(){
  char *location; 
  location =  askFile();
  initTexture(main_window, &ctext, location, &ct_width, &ct_height);
}

void  drawTexture(GLuint texName, int twidth, int theight) {
  glEnable(GL_TEXTURE_2D); 
  glBindTexture(GL_TEXTURE_2D, texName); 
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(0 + twidth, 0 + theight);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(0 + twidth, 0);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0, 0);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(0, 0 + theight);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void loadPicture(){
  glutSetWindow(main_window);
  GLuint a;
  glGenTextures(1,&a);
  char *location =  askFile();
  initTexture(main_window, &a, location, &ct_width, &ct_height);
  ctext = a;
}


void myGlutIdle( void )
{
  if ( glutGetWindow() != main_window )
    glutSetWindow(main_window);
  glutPostRedisplay();
  glui->sync_live();
}
