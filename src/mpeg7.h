#ifndef MPEG7_H
#define MPEG7_H

#include <ctype.h>
#include <fstream>
#include <sstream>
#include "feature.h"
#include "singleton.h"
#include "boost/filesystem.hpp"
#include "parameters.h"
#include "dataPoint.h"

namespace vito{
namespace features{
namespace mpeg7{

Matrix<std::vector<float> > getPatches(std::string descriptor_path);
std::string                 getDescriptorLocation(std::string loc, 
						  bool use_patches = false);
std::vector<float>          extractNumbers(std::string line);
bool                        lineIsOfType(std::string line, std::string type);
std::vector<float>          getMPEG7Descriptor(std::string p, std::string t);
void                        printPatchMatrix(const Matrix<std::vector<float> > &m);
std::vector<std::vector<float> > getAllPatches(std::vector<DataPoint> datapoints );

// Mpeg7 feature prototype
class MPEG7Feature : public Feature {
protected:
  virtual std::string getName() = 0;
  virtual float       scale(float fl) = 0;
public:
  virtual ~MPEG7Feature(){};

  // give activity using the paramers.h class
  virtual bool        isActive() = 0;

  // extract the actual descriptor
  Descriptor          extract_(MyImage *Image,
			       bool makeVisualRepresentation,
			       Magick::Image *representation);
};

// specific features:
// Edge Histogram
class EdgeHistogram : public MPEG7Feature, public Singleton<EdgeHistogram> {
  virtual std::string getName(){ return "edgehistogram";}
  virtual float       scale(float fl){return fl / 7.0;}
public:
  virtual bool       isActive(){ 
    return 
      Parameters::getInstance()->getiParameter("feature_mpeg7_edge_histogram");
  }
  virtual std::string getParameterName(){ return "mpeg7_edge_histogram";}
};

// ScalableColor
class ScalableColor : public MPEG7Feature, public Singleton<ScalableColor> {
  virtual std::string getName(){ return "scalablecolor"; };
  virtual float       scale(float fl){return fl / 255.0;}
public:
  virtual bool        isActive(){ return
      Parameters::getInstance()->getiParameter("feature_mpeg7_scalable_color"); }
  virtual std::string getParameterName(){ return "mpeg7_scalable_color";}
};

// ColorLayout
class ColorLayout : public MPEG7Feature, public Singleton<ColorLayout> {
  virtual std::string getName(){ return "colorlayout"; };
  virtual float       scale(float fl){return fl / 32.0;}
public:
  virtual bool        isActive(){ return
      Parameters::getInstance()->getiParameter("feature_mpeg7_color_layout"); }
  virtual std::string getParameterName(){ return "mpeg7_color_layout";}
};



}}}

#endif
