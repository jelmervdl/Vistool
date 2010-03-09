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
  //InitializeMagick(*argv);
  MyImage im ("../datasets/caltech101/accordion/image_0001.jpg");
  Image image = *im.getMagickImage();
  size_t width, height;
  height = image.baseRows();
  width = image.baseColumns();
  image.type(Magick::GrayscaleType);
  Pixels view(image);
  PixelPacket * pixel = view.get(0, 0, width, height);
  int max = 0;
  for(size_t y = 0; y < height; ++y){
    for(size_t x = 0; x < width; ++x){
      PixelPacket * p = pixel + x + y * width;
      if(p->red > max) max = p->red;
    }      
  }
  cout << max << endl; 
  return 0;
   

  /*
  using namespace Magick;
  MyImage im ("../datasets/caltech101/accordion/image_0001.jpg");
  Image * mim = im.getMagickImage();
  mim->type(0);
 
  float a [100];
  for(size_t y = 0 ; y < 10; ++y)
    for(size_t x = 0; x < 10; ++x)
      a[x + y * 10] = 0;
  */
  


  //  int width, height;
  //  width = 30;
  //  height = 30;
  //  (int width, int height, int noctaves, int nlevels, int o_min)
  //  VlSiftFilt * sift = vl_sift_new(width, height, 5,5,0);
  
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
