#ifndef MPEG7NEW
#define MPEG7NEW

#include "feature.h"
#include "../libs/mpeg7/Feature.h" // mpeg7 file
#include "singleton.h"

/* This file is basically a wrapper for the MPEG7 library by 
   by Muhammet Bastan, (c) October 2010 (see libs/mpeg7/Feature.g for more info)
*/

namespace vito{
namespace features{

// Color Descriptors -----------------------------------------------------------

class ColorStructure : public Feature, public Singleton<ColorStructure>{
public:
  virtual std::string getParameterName();
  virtual Descriptor  extract_(MyImage *Image,
			       bool makeVisualRespresentation,
			       Magick::Image * repr) ;
};

class ScalableColor : public Feature, public Singleton<ScalableColor>{
public:
  virtual std::string getParameterName();
  virtual Descriptor  extract_(MyImage *Image,
			       bool makeVisualRespresentation,
			       Magick::Image * repr) ;
};

class DominantColor : public Feature, public Singleton<DominantColor>{
public:
  virtual std::string getParameterName();
  virtual Descriptor extract_(MyImage *image,
			      bool makeVisRep,
			      Magick::Image *repr);
};

class ColorLayout : public Feature, public Singleton<ColorLayout>{
public:
  virtual std::string getParameterName();
  virtual Descriptor extract_(MyImage *image,
			      bool makeVisualRep,
			      Magick::Image *repr);
};

// Texture Based Descriptors ---------------------------------------------------

class EdgeHistogram : public Feature, public Singleton<EdgeHistogram>{
public:
  virtual std::string getParameterName();
  virtual Descriptor  extract_(MyImage *Image,
			       bool makeVisualRespresentation,
			       Magick::Image * repr) ;
};

class HomogeneousTexture : public Feature, public Singleton<HomogeneousTexture>{
public:
  virtual std::string getParameterName();
  virtual Descriptor extract_(MyImage *image,
			      bool makeVisualRep,
			      Magick::Image *repr);
};

/*
// Shape Based Descriptors -----------------------------------------------------

class ContourShape : public Feature, public Singleton<ContourShape>{
public:
  virtual bool isActive();
  virtual std::string getParameterName();
  virtual Descriptor extract_(MyImage *image,
			      bool makeVisualRep,
			      Magick::Image *repr);
};

class RegionShape : public Feature, public Singleton<RegionShape>{
public:
  virtual bool isActive();
  virtual std::string getParameterName();
  virtual Descriptor extract_(MyImage *image,
			      bool makeVisualRep,
			      Magick::Image *repr);
};
*/
} // namespace features
} // namespace vito


#endif
