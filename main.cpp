#include "main.h"

using namespace xercesc;

int main(int argc, char ** argv){
  Parameters * param = Parameters::getInstance();
  param->readFile("parameters.xml");
  param->printParameters();

  //param->printParameters();
  /*
  using namespace cv;
  using namespace Magick;
  using namespace std;
  Image image("/Users/mauricemulder/workspace/datasets/caltech101/BACKGROUND_Google/image_0005.jpg");
  Blob blob;
  image.magick("BGR");
  image.write(&blob);
  cout << "image's depth is: " << image.depth() << endl;
  Mat orig, hsv; 
  orig = Mat(image.size().height(),
	    image.size().width(), 
	    CV_8UC3, 
	    (void *) blob.data());
  cvtColor(orig, hsv, CV_BGR2HSV);

  int hbins = 1, sbins = 100;
  int histSize[] = {hbins, sbins};

  float hranges[] = { 0, 180 };
  float sranges[] = { 0, 256 };
  float* ranges[] = { hranges, sranges };
  MatND hist;

  int channels[] = {0, 1};
  calcHist( &hsv, 1, channels, Mat(), 
	    hist, 2, histSize, (const float **) ranges,
	    true, 
	    false );
  double maxVal=0;
  minMaxLoc(hist, 0, &maxVal, 0, 0);

  int scale = 10;
  Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC1);

  for( int h = 0; h < hbins; h++ )
    for( int s = 0; s < sbins; s++ )
      {
	float binVal = hist.at<float>(h, s);
	int intensity = cvRound(binVal*255/maxVal);
	rectangle( histImg, Point(h*scale, s*scale),
		     Point( (h+1)*scale - 1, (s+1)*scale - 1),
		     Scalar::all(intensity),
		     CV_FILLED );
      }
  imwrite("oopie.jpg", histImg);
  */
}

void printLibraries(){
  printf("Using Library: %s %d\n", "boost", 1);
  printf("Using Library: %s %d\n", "glui", 1);
  printf("Using Library: %s %d\n", "glut", 1);
  printf("Using Library: %s %d\n", "opengl", 1);
  printf("Using Library: %s %d\n", "magick++", 1);
  printf("Using Library: %s %d\n", "opencv", 1);  
}


