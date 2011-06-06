#ifndef TRUECLUSTERING_H
#define TRUECLUSTERING_H

#include "kmeansclustering.h"
#include "feature.h"
#include "boost/filesystem.hpp"


namespace vito{
namespace clustering{


class TrueClusterHistogram : public features::Feature {

public:
  //create new clustering feature by kmeans clustering
  TrueClusterHistogram(features::Feature *feature,
		       DataPointCollection dps);

  // create from stored clustercenters
  TrueClusterHistogram(std::string location,
		       Feature *feat);

  // draw patches from a datapoint collection to disk.
  void                drawRandomPatches(const DataPointCollection &dps);

  virtual std::string getParameterName();
  virtual bool        isActive(); //TODO FILL
  virtual Descriptor  extract_(MyImage *Image,
			      bool saveVisualRepresentation,
			      Magick::Image * representaton);
  virtual void        save(std::string location);


private:
  patch_collection centers;

  // feature used for comparing patches
  Feature * feature;

  // number of means in the kmeans clustering algorithm, also the
  // number of values per histogram.
  int ncenters;

  // the total number of histograms per descriptor vector is
  // ncenters^2, the total number of values in the descriptor is thus:
  // ncenters*nsegments^2
  const size_t nsegments; 

  const size_t patch_size;

  // spacing of patches
  const size_t spacing;

  // histogram algorithm to be used:
  // 0 == Hard Bag of Features
  // 1 == Soft....
  // 2 == Minimum Distance.
  const char histogram_type; // TODO parameterize

  const int parameters;
  std::string feature_type;
  
  Descriptor createHistogram(MyImage *image, 
			     size_t x_start, size_t width, 
			     size_t y_start, size_t height);

  void       addToHistogram(const patch &descriptor,
			    Descriptor &histogram,
			    bool first);

  // Hard Bag of Features
  void       hbof(const patch &descriptor,
		  Descriptor &histogram,
		  bool histogram_first);

  // Minimum Distance
  void       min(const patch &descriptor,
		 Descriptor &histogram,
		 bool first);

  patch_collection getPatches(const DataPointCollection &dps,
			      int npatches);

  void             addPatches(DataPoint dp,
			      int per_image, 
			      patch_collection &total);

  patch            randomPatch(MyImage *image);

  MyImage          randomPatchImage(MyImage *image);

  void             assertDir(std::string str);



};

}}
#endif
