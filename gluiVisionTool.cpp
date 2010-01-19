#include "gluiVisionTool.h"

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
  initTextures();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 300, 300, 0, 0, 1); // we want 2d projection mode!                                                                                       
  glMatrixMode(GL_MODELVIEW); // bring us back to model mode                                                                                          
  glDisable( GL_DEPTH_TEST); //2d, no depth                                                                                                           
  glDisable( GL_LIGHTING ); // 2d, no light  
  display();
  display();
  display(); 
  glEnd();
  glutMainLoop();
}


void display(){
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glPushMatrix();
  //  glTranslatef(140.0, 20.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawTexture(ctext, 300, 300);
  glPopMatrix();
  glLoadIdentity();
  glutSwapBuffers();
}

void initTextures(){
  char * location; 
  location = (char *) requestFile();
  initTexture(&ctext,location, &ct_width, &ct_height);
}

void  drawTexture(GLuint texName, int twidth, int theight) {
    glEnable(GL_TEXTURE_2D); /* enable texture mapping */
    glBindTexture(GL_TEXTURE_2D, texName); /* bind to our texture*/
    glPushMatrix();
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
    glPopMatrix();
}
