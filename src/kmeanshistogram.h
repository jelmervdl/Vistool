#ifndef KMEANSHISTOGRAM_H
#define KMEANSHISTOGRAM_H

#include <sstream>
#include "kmeansclustering.h"
#include "features.h"
#include "patchExtractor.h"

namespace vito{
namespace features{

class KMeansClusterHistogram : public Feature{
public:
  
  typedef clustering::patch patch;
  typedef clustering::patch_collection patch_collection;
  typedef clustering::labels labels;
  typedef clustering::label_collection label_collection;
  
protected:
  patch_collection centers;
  std::string      feature_type;
  Feature         *feature;
  const int        parameters; 

public:
  
  KMeansClusterHistogram(const DataPointCollection &dps, 
			 Feature *feat) : feature(feat), 
					  parameters(Parameters::getUniqueClone()) {
    Parameters::push(parameters);
    
    feature_type = generateName(feat);
    std::cout << "generated feature type name: " << feature_type << std::endl;
    clustering::PatchExtractor patch_extractor;
    clustering::KMeansClustering clustering;
    patch_collection patches;
    std::cout << "getting patch collection " << std::endl;
    if(feature->getParameterName().find("mpeg7") == 0)
      patches = features::mpeg7::getAllPatches(dps);
    else
      patches = patch_extractor.getPatches(dps, feature);
    std::cout << "got patches, going to cluster now" << std::endl;
    centers = clustering.cluster(patches);

    Parameters::pop();
  }
  
  KMeansClusterHistogram(std::string location, Feature *feat) :
    centers(clustering::KMeansClustering().readClusters(location + ".clustercenters")),
    feature(feat),
    parameters(Parameters::getUniqueClone()){
    std::cout << "I received this thing: " << feat << std::endl;
    std::cout << " which is a pointer to " << feat->getParameterName() << std::endl;
    Parameters::push(parameters);

    Parameters::getInstance()->readFile(location + ".xml");
    feature_type = location;

    Parameters::pop();
  }

  virtual std::string generateFileName(Feature *feat){
    return "cluster_"+ feat->getParameterName();
  }

 
  virtual void save(std::string location){
    clustering::KMeansClustering().writeClusters(centers, 
						 location);
  }

  virtual std::string getParameterName(){
    return feature_type;
  }

  virtual bool isActive(){
    std::stringstream ss;
    ss << "feature_" <<  feature_type;
    return Parameters::getInstance()->getiParameter(ss.str());
  }


  std::string generateName(Feature *feature){
    std::stringstream ss;
    ss << "kmeans_clustered_feature_using_visual_patches_"
       << feature->getParameterName();
    return ss.str();
  }

 
  virtual Descriptor  extract_(MyImage *image, 
			       bool makeVisualRepresentation, 
			       Magick::Image * magick_image){
    Parameters::push(parameters);

    clustering::KMeansClustering clustering;
    clustering::PatchExtractor patch_extractor;

    patch_collection image_patches;

    if(feature->getParameterName().find("mpeg7") == 0){
      std::vector<DataPoint> t_dps;
      t_dps.push_back(DataPoint(0,"", image->getLocation(), ""));
      image_patches = mpeg7::getAllPatches(t_dps);
    }else
      image_patches = patch_extractor.getPatches(*image, feature);

    const int kClasses = Parameters::getInstance()->getiParameter("clustering_means");    
    Descriptor histogram (kClasses);
    labels classification = clustering.classify_per_patch(centers, image_patches, &histogram);

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
    Parameters::pop();
    histogram.normalize();
    return histogram;
  }
};

}}
#endif
