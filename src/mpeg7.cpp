#include "mpeg7.h"

using std::cout;
using std::endl;

typedef Feature Mpeg7Feature;

namespace vito{
namespace features{

using std::string;

// Edge Histogram --------------------------------------------------------------
string EdgeHistogram::getParameterName(){
  return "mpeg7_edge_histogram";
}

Descriptor EdgeHistogram::extract_(MyImage *image,
				   bool makeVisRep,
				   Magick::Image *repr){
  cv::Mat &img = *image->getOpenCVMat();
  Frame* frame = new Frame(img);
  XM::EdgeHistogramDescriptor *ehd_ = Mpeg7Feature::getEdgeHistogramD(frame);
  XM::EHD *ehd = ehd_->GetEdgeHistogram();
  Descriptor desc;
  for(int i = 0; i < 80; ++i)
    desc.push_back((float) ehd->Local_Edge[i]);
  return desc;
}

// Color Structure -------------------------------------------------------------


string ColorStructure::getParameterName(){
  return "mpeg7_color_structure";
}

Descriptor ColorStructure::extract_(MyImage *image,
				   bool makeVisRep,
				   Magick::Image *repr){
  cv::Mat &img = *image->getOpenCVMat();
  Frame* frame = new Frame(img);
  XM::ColorStructureDescriptor *ehd = Mpeg7Feature::getColorStructureD(frame, 64);
  Descriptor desc;
  for(size_t i = 0; i < ehd->GetSize(); ++i)
    desc.push_back((float) ehd->GetElement(i));
  return desc;
}

// Scalable Color --------------------------------------------------------------

string ScalableColor::getParameterName(){
  return "mpeg7_scalable_color";
}

Descriptor ScalableColor::extract_(MyImage *image,
				   bool makeVisRep,
				   Magick::Image *repr){
  cv::Mat &img = *image->getOpenCVMat();
  Frame* frame = new Frame(img);
  const size_t dsize = 256;
  XM::ScalableColorDescriptor *scd = Mpeg7Feature::getScalableColorD(frame, true, dsize);
  Descriptor desc;
  for(size_t i = 0; i < dsize; ++i)
    desc.push_back((float) scd->GetCoefficient(i));
  return desc;
}

// Dominant Color --------------------------------------------------------------

string DominantColor::getParameterName(){
  return "mpeg7_dominant_color";
}

Descriptor DominantColor::extract_(MyImage *image,
				   bool makeVisRep,
				   Magick::Image *repr){
  cv::Mat &img = *image->getOpenCVMat();
  Frame* frame = new Frame(img);
  XM::DominantColorDescriptor *dcd = 
    Mpeg7Feature::getDominantColorD( frame , false ); // don't normalize
  size_t nColors = dcd->GetDominantColorsNumber();
  XM::DOMCOL *colors = dcd->GetDominantColors();
  cout << "we've got: " << nColors << " dominant colors" << endl;
  Descriptor desc;
  for(size_t i = 0; i < nColors; ++i){
    cout << "color " << i << "  percentage: " << colors[i].m_Percentage;
    for(size_t j = 0; j < 3; ++j){
      cout << " " <<  j << " " << colors[i].m_ColorValue[j];
      desc.push_back((float) colors[i].m_ColorValue[j]);
    } // for j
    cout << endl;
  } // for i
  desc.resize(24, 0.0);
  return desc;
}

// Color Layout ----------------------------------------------------------------

string ColorLayout::getParameterName(){
  return "mpeg7_color_layout";
}

Descriptor ColorLayout::extract_(MyImage *image,
				 bool makeVisrep,
				 Magick::Image *repr){
  cv::Mat &img = *image->getOpenCVMat();
  Frame *frame = new Frame(img);
  XM::ColorLayoutDescriptor *xmdesc = 
    Mpeg7Feature::getColorLayoutD(frame);
  size_t nY = xmdesc->GetNumberOfYCoeff();
  size_t nC = xmdesc->GetNumberOfCCoeff();
  int *YCoeff  = xmdesc->GetYCoeff();
  int *CbCoeff = xmdesc->GetCbCoeff();
  int *CrCoeff = xmdesc->GetCrCoeff();

  // write coefficients to single descriptor
  Descriptor desc;
  for(size_t i = 0; i < nY; i++)
    desc.push_back((float) YCoeff[i]);
  for(size_t i = 0; i < nC; i++)
    desc.push_back((float) CbCoeff[i]);
  for(size_t i = 0; i < nC; i++)
    desc.push_back((float) CrCoeff[i]);
  return desc;
}

// Homogeneous Texture ---------------------------------------------------------


string HomogeneousTexture::getParameterName(){
  return "mpeg7_homogeneous_texture";
}

Descriptor HomogeneousTexture::extract_(MyImage *image,
					bool makeVisrep,
					Magick::Image *repr){
  cv::Mat non_gray = *image->getOpenCVMat();
  cv::Mat img = Mat( non_gray.rows, non_gray.cols, CV_8UC1);
  cvtColor(non_gray, img, CV_BGR2GRAY);
  Frame *frame = new Frame(img.rows, img.cols, false, true, false);
  frame->setGray(img);
  XM::HomogeneousTextureDescriptor *xmdesc = 
    Mpeg7Feature::getHomogeneousTextureD(frame, true);
  Descriptor desc;
  for(int i = 0; i < 62; ++i)
    desc.push_back((float) xmdesc->feature[i]);
  delete xmdesc;
  return desc;
}

/*

// Contour Shape ---------------------------------------------------------------
bool ContourShape::isActive(){
  return true;
}

string ContourShape::getParameterName(){
  return "ContourShape";
}

Descriptor ContourShape::extract_(MyImage *image,
				  bool makeVisrep,
				  Magick::Image *repr){
  cv::Mat &img = *image->getOpenCVMat();
  Frame *frame = new Frame(img);
  XM::ContourShapeDescriptor *xmdesc = 
    Mpeg7Feature::getContourShapeD(frame);
  // some cool code ....
  xmdesc->Print();
  Descriptor desc;
  return desc;
}

// Region Shape ----------------------------------------------------------------

bool RegionShape::isActive(){
  return true;
}

string RegionShape::getParameterName(){
  return "RegionShape";
}

Descriptor RegionShape::extract_(MyImage *image,
				 bool makeVisrep,
				 Magick::Image *repr){
  cv::Mat &img = *image->getOpenCVMat();
  Frame *frame = new Frame(img);
  XM::RegionShapeDescriptor *xmdesc = 
    Mpeg7Feature::getRegionShapeD(frame);
  // some cool code ....
  Descriptor desc;
  return desc;
}
*/
} // namespace features
} // namespace vito
