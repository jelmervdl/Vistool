#include "gluiVisionTool.h"


using namespace std;
GLUI_StaticText *txt;
GLUI *glui;
GLUI *classes;
GLuint ctext;
size_t ct_width;
size_t ct_height;
size_t window_width;
size_t window_height;
int main_window;
Dataset * currentdb;

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

void askDataset(){
  loadDataset(askFile());
}

void loadDataset(string location){
  classes = GLUI_Master.create_glui( "classes", 0, 950, 250 );
  currentdb = new Dataset(location);
  vector<Category> * cats = currentdb->getCategories();
  size_t c = 0;
  classes->add_button( "Print Enabled", 0, (GLUI_Update_CB)test );
  classes->add_button( "Extract Descriptors", 0, (GLUI_Update_CB)extractFeatures );
  classes->add_column(true);
  if(currentdb != NULL){
    for(size_t i = 0; i < cats->size(); ++i){
      classes->add_checkbox(
			    (const char *)cats->at(i).getName().c_str(),
			    cats->at(i).getEnabled(),
			    1, (GLUI_Update_CB) NULL);
      c++;
      if(c%20==0)
	classes->add_column(false);
    }
  }
}

void extractFeatures(){
  txt->set_text("extracting...");
  glutPostRedisplay();
  FeatureExtractor f;
  f.saveDescriptorsToFile(currentdb);
  txt->set_text("done");
}

void test(){
  currentdb->print();
}

void loadPicture(){
  glutSetWindow(main_window);
  GLuint a;
  glGenTextures(1,&a);
  char *location =  askFile();
  initTexture(main_window, &a, location, &ct_width, &ct_height);
  ctext = a;
}

void initTextures(){
  char *location; 
  location =  askFile();
  initTexture(main_window, &ctext, location, &ct_width, &ct_height);
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


void myGlutIdle( void )
{
  if ( glutGetWindow() != main_window )
    glutSetWindow(main_window);
  glutPostRedisplay();
  glui->sync_live();
}

void initGlui(){
  glui = GLUI_Master.create_glui( "Control", 0, 950, 50 );
  glui->add_statictext( "Vision Tool" ); 
  txt = glui->add_statictext( "waiting" ); 
  glui->add_button( "Quit", 0,(GLUI_Update_CB)exit );
  glui->add_button( "Load Picture", 0, (GLUI_Update_CB)loadPicture );
  glui->add_button( "Load Dataset", 0, (GLUI_Update_CB)askDataset );
  glui->add_button( "Load Caltech", 0, (GLUI_Update_CB)loadCaltech );
  glui->set_main_gfx_window(main_window);
  GLUI_Master.set_glutIdleFunc( myGlutIdle );
}

void loadCaltech(){
  loadDataset("/Users/mauricemulder/workspace/datasets/caltech101/");
}
