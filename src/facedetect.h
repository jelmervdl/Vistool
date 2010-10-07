#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#define CV_NO_BACKWARD_COMPATIBILITY

#include "parameters.h"
#include "singleton.h"
#include "cv.h"
#include "highgui.h"
#include "feature.h"

#include <iostream>
#include <cstdio>

#ifdef _EiC
#define WIN32
#endif

namespace vito{
namespace features{

int detect( cv::Mat& img,
	     cv::CascadeClassifier& cascade, 
	     cv::CascadeClassifier& nestedCascade,
	     double scale);

class FaceFeature : public Feature, public Singleton<FaceFeature> {
public:
  std::string getParameterName(){
    return "face";
  };
  bool isActive(){
    return (Parameters::getInstance()->getiParameter("feature_face") > 0);
  };

  virtual Descriptor extract_(MyImage *Image, 
			      bool makeVisualRepresentation, 
			      Magick::Image * representation); 
};

}}

#endif
