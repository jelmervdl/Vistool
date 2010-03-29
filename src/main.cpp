#include "main.h"
#define PI 3.14159265

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
  Parameters * p = Parameters::getInstance();
  p->readFile((char *) "parameters.xml");
  //start(argc, argv);
  


// is it nan? %d is it > 0? %d is it < 0? %d\n",
	 //	 nan, nan == nan, nan > );



  /* Radial guide:
     0.0    -> ( 0,  1)
     0.5 PI -> ( 1,  0)
     1.0 PI -> ( 0, -1)   
     1.5 PI -> (-1, -1)
  */
  /*
  MyImage im ("../datasets/caltech101/accordion/image_0001.jpg");
  Matrix<float> grayscale = im.getGrayscaleMatrix();
  Matrix<Gradient> gradient = imageGradient(&grayscale);  
  SiftDescriptor sift;
  vector<sift::KeyPoint> keypoints 
    = sift::divideIntoKeypoints( im.get_width(),
				 im.get_height(),
				 10, 10);
  vector<  > descriptors(keypoints.size());
  Image magick_image = *im.getMagickImage();
  int orientations = 16;
  int window = 10;
  for(size_t i = 0 ; i < keypoints.size(); ++i){
    descriptors[i] = sift.getKeyPointDescriptor(&gradient, &keypoints[i], window, orientations);
    float bin_size = ((2 * PI) / orientations);
    magick_image.strokeColor("green");
    magick_image.fillColor(Color());
    magick_image.draw( DrawableCircle(keypoints[i].get_center_x(), keypoints[i].get_center_y(),
				      keypoints[i].get_center_x() + window, keypoints[i].get_center_y() + window));
    magick_image.strokeColor("red");
    magick_image.strokeWidth(1);
    for(int ori = 0; ori < orientations; ++ori)
      {
	float angle = (bin_size * (ori + 1)) - (0.5 * bin_size);
	printf("angle: %.2f \t dx: %.2f dy %.2f \tbin val: %.2f\n", 
	       angle / PI, sin(angle), cos(angle), descriptors[i][ori]);
	magick_image.draw( DrawableLine(keypoints[i].get_center_x(),
					keypoints[i].get_center_y(),
					keypoints[i].get_center_x() + descriptors[i][ori] * 1 * sin(angle),
					keypoints[i].get_center_y() - descriptors[i][ori] * 1 * cos(angle)));
      } 
    cout << endl;
  }

  magick_image.write("output.png");
  */
  /*

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
  */
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
