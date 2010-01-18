#include "gluiVisionTool.h"

GluiVisionTool::GluiVisionTool(int argc, char ** argv){
  glutInit(&argc, argv);
}

void GluiVisionTool::start(){
  printf("Starting up glut...\n");
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 300, 300 );
  main_window = glutCreateWindow( "GLUI Example 3" );
  glutMainLoop();
}
