#include "gluiVisionTool.h"

using namespace std;

namespace vito{
namespace gui{

void start(int argc, char **argv){
  glutInit(&argc, argv); 
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  setupWindow();
  glutDisplayFunc(display);
  setupOpenGL();
  display();
  initGlui();
  glutMainLoop();
}

}}
