#define CV_NO_BACKWARD_COMPATIBILITY

#include "cv.h"
#include "highgui.h"

#include <iostream>
#include <cstdio>

#ifdef _EiC
#define WIN32
#endif

void detectAndDraw( cv::Mat& img,
		    cv::CascadeClassifier& cascade, 
		    cv::CascadeClassifier& nestedCascade,
		    double scale);
