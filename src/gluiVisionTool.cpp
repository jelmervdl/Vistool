#include "gluiVisionTool.h"

using namespace std;



namespace vito{
namespace gui{

void start(int argc, char **argv){
  glutInit(&argc, argv); // obligatory glut call
  printf("Starting up glut...\n"); 
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  setupWindow();
  glutDisplayFunc(display);
  setupOpenGL();
  display();
  initGlui();
  glutMainLoop();
}

}}
