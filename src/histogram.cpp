#include "histogram.h"

using std::cout;
using std::endl;
using std::vector;

using cv::Mat;
using cv::MatND;

using Magick::Image;
using Magick::Geometry;
using Magick::Color;
using Magick::ColorGray;
using Magick::DrawableRectangle;

namespace vito{
namespace features{

Histogram::~Histogram(){
}

bool Histogram::isActive(){
  return (Parameters::getInstance()->getiParameter("feature_histogram") > 0);
}

Descriptor Histogram::extract_(MyImage *image,  
				 bool saveVisualRepresentation,
				 Image *canvas){
  Mat * hsv = image->getOpenCVMat();
  Parameters * p = Parameters::getInstance();
  int 
    hbins = p->getiParameter("histogram_hbins"), 
    sbins = p->getiParameter("histogram_sbins");
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
  const int bin_representation_size = 10;
  //ready the canvas in case we'll need to save a visual representation
  if(saveVisualRepresentation)
    *canvas = Image(Geometry(sbins * bin_representation_size, 
			     hbins * bin_representation_size),
		    Color("black"));
  Descriptor data;
  // save the binning for each hue and saturation value
  for( int h = 0; h < hbins; h++ ){
    for( int s = 0; s < sbins; s++ ){
      float binVal = hist.at<float>(h, s);
      binVal /= maxVal;
      data.push_back((float) binVal);
      if(saveVisualRepresentation){
	float intensity = binVal / maxVal;
	canvas->fillColor(ColorGray(intensity));
	canvas->draw( DrawableRectangle(h * bin_representation_size,
					s * bin_representation_size,
					(h + 1) * bin_representation_size,
					(s + 1) * bin_representation_size));


      }
    }
  }
  data.normalize();
  return data;
}

}}
