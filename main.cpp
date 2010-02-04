#include "main.h"

int main(int argc, char ** argv){
  printLibraries();
  //saveFile();
  printf("starting up vision tool..\n");
  using namespace cv;
  using namespace Magick;
  using namespace std;
  Image image("/Users/mauricemulder/workspace/datasets/caltech101/BACKGROUND_Google/image_0005.jpg");
  Blob blob;
  image.magick("BGR");
  image.write(&blob);
  cout << "image's depth is: " << image.depth() << endl;
  Mat aap, hond; 
  aap = Mat(image.size().height(),
	    image.size().width(), 
	    CV_8UC3, 
	    (void *) blob.data());
  cvtColor(aap, hond, CV_BGR2RGB);
  int rbins, bbins, gbins;
  rbins = 255;
  bbins = 255;
  gbins = 255;
  int histSize[] = {rbins, bbins, gbins};
  float rranges[] = {0, 255};
  float granges[] = {0, 255};
  float branges[] = {0, 255};
  float * ranges [] = {rranges, branges, granges};
  int channels [] = {0, 1 ,2};
  MatND hist;
  calcHist( &hond, 1, channels, Mat(), hist, 3, histSize, 
  return  0;
}

void printLibraries(){
  printf("Using Library: %s %d\n", "boost", 1);
  printf("Using Library: %s %d\n", "glui", 1);
  printf("Using Library: %s %d\n", "glut", 1);
  printf("Using Library: %s %d\n", "opengl", 1);
  printf("Using Library: %s %d\n", "magick++", 1);
  printf("Using Library: %s %d\n", "opencv", 1);  
}
