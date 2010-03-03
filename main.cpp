#include "main.h"

using namespace xercesc;
int main(int argc, char ** argv){
  if(argc > 1){
    string aap = argv[1];
    if(aap == "test"){
      testing::testAll();
      return 0;
    }
  }
  VlSiftFilt * a =  vl_sift_new(100,100,5,5,0);
  vl_sift_pix image [100*100];
  vl_sift_pix desc [2*100*100];
  vl_sift_process_first_octave(a, image);
  //vl_sift_calc_raw_descriptor();
  //Parameters * p = Parameters::getInstance();
  //p->readFile((char *) "parameters.xml");
  //start(argc, argv);
  
}

void Libraries(){
  printf("Using Library: %s %d\n", "boost", 1);
  printf("Using Library: %s %d\n", "glui", 1);
  printf("Using Library: %s %d\n", "glut", 1);
  printf("Using Library: %s %d\n", "opengl", 1);
  printf("Using Library: %s %d\n", "magick++", 1);
  printf("Using Library: %s %d\n", "opencv", 1);  
}

