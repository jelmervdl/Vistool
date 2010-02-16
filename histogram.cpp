#include "histogram.h"

bool Histogram::instanceFlag= false;
Histogram * Histogram::singleton = NULL;

Histogram * Histogram::getInstance(){
    if(!instanceFlag){
    singleton = new Histogram();
    instanceFlag = true;
  }
  return singleton;
}

Histogram::~Histogram(){
  instanceFlag =false;
}

Histogram::Histogram(){
  cout << "making histogram" << endl;
}

vector<float> Histogram::extract(MyImage * image){
  Mat * hsv = image->getOpenCVMat();
  Parameters * p = Parameters::getInstance();
  if(!p->hasHistogram()){
    cout << "histogram parameters not found" << endl;
    throw NO_PARAMETERS;
  }
  int hbins = p->getiParameter("hbins"), sbins = p->getiParameter("sbins");
  int histSize[] = {hbins, sbins};

  float hranges[] = { 0, 180 };
  float sranges[] = { 0, 256 };
  float* ranges[] = { hranges, sranges };
  MatND hist;

  int channels[] = {0, 1};
  calcHist( hsv, 1, channels, Mat(), 
	    hist, 2, histSize, (const float **) ranges,
	    true, 
	    false );
  double maxVal=0;
  minMaxLoc(hist, 0, &maxVal, 0, 0);

  int scale = 10;
  Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC1);
  vector<float> data;
  for( int h = 0; h < hbins; h++ )
    for( int s = 0; s < sbins; s++ )
      {
	float binVal = hist.at<float>(h, s);
	data.push_back(binVal);
	int intensity = cvRound(binVal*255/maxVal);
	rectangle( histImg, Point(h*scale, s*scale),
		     Point( (h+1)*scale - 1, (s+1)*scale - 1),
		     Scalar::all(intensity),
		     CV_FILLED );
      }
  return data;
}
