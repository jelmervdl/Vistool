#include "main.h"

int main(int argc, char ** argv){
  printf("starting up vision tool..\n");
  //const char * string = requestFile();
  GluiVisionTool  vis =  GluiVisionTool( argc , argv);
  vis.start();
  //printf("done%s\n", string);
  return  0;
}
