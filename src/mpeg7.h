#ifndef MPEG7_H
#define MPEG7_H

#include <ctype.h>
#include <fstream>
#include <sstream>
#include "feature.h"
#include "singleton.h"
#include "boost/filesystem.hpp"

namespace vito{
namespace features{
namespace mpeg7{

class MPEG7Feature : public Feature {
protected:
  std::string        getDescriptorLocation(std::string loc);

  std::vector<float> getMPEG7Descriptor(std::string descriptor_path, 
				    std::string type);

  bool               lineIsOfType(std::string line, 
				  std::string type);

  std::vector<float> extractNumbers(std::string line);

  virtual std::string        getName() = 0;
public:
  virtual bool isActive() = 0;
  Descriptor extract_(MyImage *Image,
			      bool makeVisualRepresentation,
			      Magick::Image *representation);
};

class EdgeHistogram : public MPEG7Feature, public Singleton<EdgeHistogram> {
  virtual std::string getName(){ return "edgehistogram";}
public:
  virtual bool        isActive(){ 
    return 
      Parameters::getInstance()->getiParameter("feature_mpeg7_edge_histogram") 
      > 0; }
};

class ScalableColor : public MPEG7Feature, public Singleton<ScalableColor> {
  virtual std::string getName(){ return "scalablecolor"; };
public:
  virtual bool        isActive(){ return
      Parameters::getInstance()->getiParameter("feature_mpeg7_scalable_color") 
      > 0; }
};

class ColorLayout : public MPEG7Feature, public Singleton<ColorLayout> {
  virtual std::string getName(){ return "colorlayout"; };
public:
  virtual bool        isActive(){ return
      Parameters::getInstance()->getiParameter("feature_mpeg7_color_layout") 
      > 0; }
};



}}}

#endif
