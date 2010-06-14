#ifndef KMEANSHISTOGRAM_H
#define KMEANSHISTOGRAM_H

#include <sstream>
#include "kmeansclustering.h"
#include "feature.h"
#include "patchExtractor.h"

namespace vito{
namespace features{

class KMeansClusterHistogram  : public Feature{
public:

  typedef clustering::patch patch;
  typedef clustering::patch_collection patch_collection;
  typedef clustering::labels labels;
  typedef clustering::label_collection label_collection;

protected:
  patch_collection centers;
  std::string      feature_type;
  Feature         *feature;

public:

  virtual std::string getParameterName(){
    return feature_type;
  }

  virtual bool isActive(){
    std::stringstream ss;
    ss << "feature_" <<  feature_type;
    std::cout << "is this feature active?:" << ss.str() << " answer: " 
	      << Parameters::getInstance()->getiParameter(ss.str()) << std::endl;
    return Parameters::getInstance()->getiParameter(ss.str());
  }


  KMeansClusterHistogram(std::vector<DataPoint> *dps, Feature *feat) : feature(feat) {
    std::stringstream ss;
    ss << "kmeans_clustered_feature_using_visual_patches_"
       << feature->getParameterName() << "_of_" 
       << dps->size() << "_images";
    feature_type = ss.str();
    clustering::PatchExtractor patch_extractor;
    clustering::KMeansClustering clustering;

    std::cout << "finding mpeg7 in feature name? " 
	      << feature->getParameterName().find("mpeg7") << std::endl;

    patch_collection patches;
    if(feature->getParameterName().find("mpeg7") == 0)
      patches = features::mpeg7::getAllPatches(*dps);
    else
      patches = patch_extractor.getPatches(dps, feature);
    centers = clustering.cluster(patches);
  }

  virtual Descriptor  extract_(MyImage *image, 
			       bool makeVisualRepresentation, 
			       Magick::Image * magick_image){
    clustering::KMeansClustering clustering;
    clustering::PatchExtractor patch_extractor;

    patch_collection image_patches;
    std::cout << "finding mpeg7 in feature name? " 
	      << feature->getParameterName().find("mpeg7") << std::endl;


    if(feature->getParameterName().find("mpeg7") == 0){
      std::vector<DataPoint> t_dps;
      t_dps.push_back(DataPoint(0,"", image->getLocation(), ""));
      image_patches = mpeg7::getAllPatches(t_dps);
    }else
      image_patches = patch_extractor.getPatches(*image, feature);

    labels classification = 
      clustering.classify_per_patch(centers, image_patches);

    std::cout  << "just made a class of size: " << classification.size() << std::endl;
    std::cout << " with content: " << std::endl;
    for(size_t i = 0; i < classification.size(); i++)
      std::cout << classification[i]  << " ";
    std::cout << std::endl;

    const int kClasses = 50;    
    std::vector<float> histogram (kClasses);
    std::cout << "the hist content: " << std::endl;
    for(size_t i = 0; i < classification.size(); i++)
      histogram[classification[i]]++;
    for(size_t i = 0; i < histogram.size(); i++){
      //histogram[i] /= (float) classification.size();
      std::cout << i << ":" << histogram[i] << ", ";
    }
    std::cout << std::endl;

    if(makeVisualRepresentation){
      *magick_image = *image->getMagickImage(); 
      Magick::Image &mag = *magick_image;

      std::vector<Magick::Color> colors;
      colors.push_back(Magick::Color("black"));
      colors.push_back(Magick::Color("green"));
      colors.push_back(Magick::Color("yellow"));
      colors.push_back(Magick::Color("red"));
      colors.push_back(Magick::Color("purple"));
      colors.push_back(Magick::Color("blue"));
      colors.push_back(Magick::Color("brown"));
      colors.push_back(Magick::Color("pink"));
      colors.push_back(Magick::Color("gray"));

      for(int x = 0; x < 10; x++){
	for(int y = 0; y < 10; y++){
	  const int index = 10 * x + y;
	  int width = mag.columns();
	  int height = mag.rows();
	  int left = (x / (float) 10) * width;
	  int right = ((1 + x) / (float) 10) * width;
	  int up = (y / (float) 10) * height;
	  int down = ((1 + y) / (float) 10) * height;
	  Magick::Color color;
	  color.alpha(10.0);
	  mag.fillColor(color);
	  mag.strokeColor("red");
	  mag.draw(Magick::DrawableRectangle(left, up, right, down));
	  std::stringstream b;
	  b << classification[index];
	  mag.fillColor(colors[classification[index] % colors.size()]);
	  mag.strokeColor(color);
	  int tleft = left + 10;
	  int tup = up + 10;
	  if(tleft > width)
	    tleft = left;
	  if(tup > height)
	    tup = up;
	  Magick::DrawableText text(tleft, tup, b.str());
	  mag.draw(text);
      }
    }
    }


    return histogram;
  }
};

}}
#endif
