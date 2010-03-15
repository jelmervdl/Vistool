#include "main.h"

using namespace gradient;
 
using namespace xercesc;
int main(int argc, char ** argv){
  if(argc > 1){
    string aap = argv[1];
    if(aap == "test"){
      testing::testAll();
      return 0;
    }
  }
  MyImage im ("../datasets/caltech101/airplanes/image_0005.jpg");
  Matrix<float>  matrix =  im.getGrayscaleMatrix();
  cout << matrix.get_height() << endl;
  cout << "1" << endl;
 Matrix<Gradient> gradient = imageGradient(&matrix);
  cout << "2" << endl;
 Image drawGradients(
		     Geometry(gradient.get_width(), gradient.get_height()),
		     Color("black"));
 vector<float> b;
 b.resize(12);
 for(size_t x = 0; x < gradient.get_width(); ++x){
   for(size_t y = 0; y < gradient.get_height(); ++y){
     bin(gradient.at(x,y), &b, 1.0);
     float magn = gradient.at(x,y)->get_magnitude();
     ColorGray set_color(magn);
     drawGradients.pixelColor(x, y, set_color);
   }
 }
 
 vector<sift::KeyPoint> keypoints 
   = sift::divideIntoKeypoints(gradient.get_width(),
			       gradient.get_height(),
			        10, 10);
 for(vector<sift::KeyPoint>::iterator kp = keypoints.begin();
     kp != keypoints.end();
     ++kp)
   size_t descriptor_window = 15;


 drawGradients.write("grads.jpg");

 //binning algorithm

 for(size_t i = 0; i < b.size(); ++i)
   cout << "i:" << b[i] << endl;

  return 0;
}

void Libraries(){
  printf("Using Library: %s %d\n", "boost", 1);
  printf("Using Library: %s %d\n", "glui", 1);
  printf("Using Library: %s %d\n", "glut", 1);
  printf("Using Library: %s %d\n", "opengl", 1);
  printf("Using Library: %s %d\n", "magick++", 1);
  printf("Using Library: %s %d\n", "opencv", 1);  
}
