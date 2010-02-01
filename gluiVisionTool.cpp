#include "gluiVisionTool.h"

GLUI * glui;
GLuint ctext;
size_t ct_width;
size_t ct_height;
int main_window;

// current texture identified + properties

void start(int argc, char ** argv){
  glutInit(&argc, argv);
  printf("Starting up glut...\n");
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 300, 300 );
  main_window = glutCreateWindow( "GLUI Example 3" );
  glutDisplayFunc(display);
  glGenTextures(1, &ctext);
  initTextures();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 300, 300, 0, 0, 1); // we want 2d projection mode!                                                                                       
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
  glui = GLUI_Master.create_glui( "GLUI", 0, 400, 50 );
  glui->add_statictext( "Cool Vision Tool" ); 
  glui->add_button( "Quit", 0,(GLUI_Update_CB)exit );
  glui->add_button( "Load Picture", 0, (GLUI_Update_CB)loadPicture );
  glui->set_main_gfx_window(main_window);
  GLUI_Master.set_glutIdleFunc( myGlutIdle );
}

void display(void){
  using namespace std;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW); // bring us back to model mode                                                                                          
  glLoadIdentity();
  cout << "drawing texture at" << ctext << endl;
  cout << "main window is " << main_window << "current window is: " << glutGetWindow() << endl;;
  drawTexture(ctext, 300, 300);
  glutSwapBuffers();
}

void initTextures(){
  char * location; 
  location =  askFile();
  initTexture(main_window, &ctext, location, &ct_width, &ct_height);
}

void  drawTexture(GLuint texName, int twidth, int theight) {
  glEnable(GL_TEXTURE_2D); /* enable texture mapping */
  glBindTexture(GL_TEXTURE_2D, texName); /* bind to our texture*/
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(0, 0);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(0 + twidth, 0);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(0 + twidth, 0 + theight);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0, 0 + theight);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void loadPicture(){
  //  glDeleteTextures(1, &ctext);
  glutSetWindow(main_window);
  GLuint a;
  glGenTextures(1,&a);
  char * location =  askFile();
  initTexture(main_window, &a, location, &ct_width, &ct_height);
  ctext = a;
}


void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is                                                                                                                                                                  
     undefined during an idle callback.  So we need to explicitly change                                                                                                                                                         
     it if necessary */
  if ( glutGetWindow() != main_window )
    glutSetWindow(main_window);
  glutPostRedisplay();

  /****************************************************************/
  /*            This demonstrates GLUI::sync_live()               */
  /*   We change the value of a variable that is 'live' to some   */
  /*   control.  We then call sync_live, and the control          */
  /*   associated with that variable is automatically updated     */
  /*   with the new value.  This frees the programmer from having */
  /*   to always remember which variables are used by controls -  */
  /*   simply change whatever variables are necessary, then sync  */
  /*   the live ones all at once with a single call to sync_live  */
  /****************************************************************/
  glui->sync_live();
}
