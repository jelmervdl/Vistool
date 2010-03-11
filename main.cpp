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
  MyImage im ("../datasets/caltech101/accordion/image_0001.jpg");
  Matrix<float> * gray =  im.getGrayscaleMatrix();
  /*
  Image image = *im.getMagickImage();
  size_t width, height;
  height = image.baseRows();
  width = image.baseColumns();
  image.type(Magick::GrayscaleType);
  Pixels view(image);
  vl_sift_pix shades [width * height];
  cout << "size of a float? " << sizeof(float) << endl;
  for(size_t y = 0; y < height; ++y)
    for(size_t x = 0; x < width; ++x)
      shades[x + y * width] = ((ColorGray) image.pixelColor(x,y)).shade();
  vl_sift_pix desc [width * height * 2];
  VlSiftFilt * sift_filter = vl_sift_new(width, height, 1, 1, 0);
  vl_sift_calc_raw_descriptor(sift_filter, shades, desc,
			      width, height,
			      0.5, 0.5,
			      1.0, 3.14);
  for(size_t y = 0; y < height; ++y){
    for(size_t x = 0; x < width; ++x)
      cout << desc[x + y * width] << " ";
    cout << endl;
  }
  */

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
