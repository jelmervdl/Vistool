#include "featureExtractor.h"

using namespace Magick;
using namespace std;
using namespace cv;
using namespace boost::filesystem;


void FeatureExtractor::createAndSaveDescriptors(vector<Category> * particip){
  cout << "Extracting Features..." << endl;
  for(vector<Category>::iterator category = particip->begin();
	category != particip->end();
	++category){
    string name = category->getName();
    cout << "class: " << name << endl;
    vector<string> files = category->file_list();
    string root = category->getRoot();
    string aap = DESCRIPTOR_LOCATION;
    path p = complete(path(aap+name, native));
    if(!is_directory(p))
      create_directory(p);
    for(vector<string>::iterator file = files.begin(); file != files.end(); ++file ){
      MyImage image(root+"/"+*file);
      vector<float> features = extractHistogram(&image);
      writeDescriptor(&features, aap+name+"/"+*file+".desc");
    }
    cout << "done!" << endl;
  }
}

vector<float> FeatureExtractor::extractHistogram(MyImage * image){
  Mat * hsv = image->getOpenCVMat();
  Parameters * p = Parameters::getInstance();
  if(!p->hasHistogram()){
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

