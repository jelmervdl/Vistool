#include "histogram.h"

Histogram::Histogram(){
  cout << "making histogram" << endl;
}

vector<float> Histogram::extract(MyImage *image,  
				 bool saveVisualRepresentation,
				 Image *canvas){
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
  if(saveVisualRepresentation)
    *canvas = Image(Geometry(sbins*scale, hbins*scale), Color("black"));
  vector<float> data;
  for( int h = 0; h < hbins; h++ )
    for( int s = 0; s < sbins; s++ )
      {
	float binVal = hist.at<float>(h, s);
	data.push_back(binVal);
	if(saveVisualRepresentation){
	  float intensity = binVal / maxVal;
	  canvas->fillColor(ColorGray(intensity));
	  canvas->draw( DrawableRectangle(h * scale, s * scale,
					   (h + 1) * scale, (s + 1) * scale));
	}
      }
  return data;
}
