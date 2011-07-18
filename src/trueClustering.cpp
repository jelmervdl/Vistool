#include "trueClustering.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::stringstream;

using boost::filesystem::path;
using boost::filesystem::native;
using boost::filesystem::complete;


namespace vito{
namespace clustering{

TrueClusterHistogram::TrueClusterHistogram(features::Feature *feature_,
					   DataPointCollection dps):
  feature(feature_), 
  ncenters(Parameters::getInstance()->getiParameter("clustering_means")), 
  nsegments(1), 
  patch_size(Parameters::getInstance()->getiParameter("clustering_patch_size")),
  spacing
(Parameters::getInstance()->getiParameter("clustering_spacing")),
  histogram_type(Parameters::getInstance()->
		 getiParameter("clustering_histogram_type")),
  parameters(Parameters::getUniqueClone()),
  feature_type("")
{
  
  patch_collection patches = getPatches(dps, ncenters * 100);
  KMeansClustering clustering;
  centers = clustering.cluster(patches);
}

TrueClusterHistogram::TrueClusterHistogram(std::string location,
					   Feature *feat) :
  centers(clustering::KMeansClustering().readClusters(location + ".clustercenters")),
  feature(feat), 
  ncenters(Parameters::getInstance()->getiParameter("clustering_means")), 
  nsegments(1), 
  patch_size(Parameters::getInstance()->getiParameter("clustering_patch_size")),
  spacing(Parameters::getInstance()->getiParameter("clustering_spacing")),
  histogram_type(Parameters::getInstance()->
		 getiParameter("clustering_histogram_type")),
  parameters(Parameters::getUniqueClone()),
  feature_type(location){
  Parameters::push(parameters);
  Parameters::getInstance()->readFile(location + ".xml");
  Parameters::pop();
}


string TrueClusterHistogram::getParameterName(){
  stringstream name;
  name << "trueclustering" << "c" << ncenters
       << "ps" <<  patch_size  
       << "sp" << 8
       << "ht" << (int) histogram_type
       << feature_type;
  return name.str();
}

bool TrueClusterHistogram::isActive(){
  return true;
}

void TrueClusterHistogram::assertDir(string str){
  path p = complete(path(str, native));
  if(!is_directory(p)){
    cout << "creating directory " << str << endl;
    create_directory(p);
  }
}

void TrueClusterHistogram::drawRandomPatches(const DataPointCollection &dps){
  cout << "drawing random patches: " << endl;
  const size_t npatches = 30;
  size_t filename = 0;
  // iterate datapoints
  for(DataPointCollection::const_iterator dp = dps.begin(); dp != dps.end(); ++dp){ 
    MyImage dp_image(*dp);
    // iterate patches
    for(size_t current_patch = 0; current_patch < npatches; current_patch++){

      // find center closest to dp
      MyImage patch_image = randomPatchImage(&dp_image);
      Parameters::push(parameters);
      Descriptor current_patch_desc = feature->extract(&patch_image);
      Parameters::pop();
      size_t closest = 0;
      float dist = -1.0;
      for(patch_collection::iterator c = centers.begin(); 
	  c != centers.end(); ++c){
	float current_distance = current_patch_desc.distance(*c); 
	if(dist == -1.0 || current_distance < dist){
	  closest = c - centers.begin();
	  dist = current_distance;
	}
      }

      //write patch to appropriate cluster nr directory
      stringstream impath;
      cout << "writing image.." << endl;
      impath << "patch_images/";
      assertDir(impath.str());
      impath << closest << "/";
      assertDir(impath.str());
      impath << filename << ".jpg";
      filename++;
      patch_image.getMagickImage()->write(impath.str());
    }
  }
}

patch_collection TrueClusterHistogram::getPatches(const DataPointCollection &dps,
						  int npatches){
  cout << "npatches: " << npatches << " dps size: " << dps.size() << endl;
  int per_image = 20;//1 + (npatches / dps.size());
  cout << "extracting " << per_image << " per image " << endl;
  typedef DataPointCollection::const_iterator dpit;
  patch_collection total;
  for(dpit i = dps.begin(); i != dps.end(); ++i){
    addPatches(*i, per_image, total);
  }
  return total;
}

void TrueClusterHistogram::addPatches(DataPoint dp,
				      int per_image, 
				      patch_collection &total){
  MyImage myimage(dp);
  for(int i = 0; i < per_image; i++)
    total.push_back(randomPatch(&myimage));
}

patch TrueClusterHistogram::randomPatch(MyImage *image){
  MyImage subImage = randomPatchImage(image);
  Parameters::push(parameters);
  Descriptor desc = feature->extract(&subImage);
  Parameters::pop();
  return desc;

}


MyImage TrueClusterHistogram::randomPatchImage(MyImage *image){
int x = rand() % (image->get_width() - patch_size);
  int y = rand() % (image->get_height() - patch_size);
  Magick::Image newim = *image->getMagickImage(); 
  newim.crop(Magick::Geometry(patch_size, patch_size, x, y));
  stringstream delme;
  MyImage subImage(newim);
  return subImage;
}

Descriptor TrueClusterHistogram::extract_( MyImage *image,
					  bool save,
					   Magick::Image * representaton){
  Descriptor concatinated_histograms;
  const size_t width = image->get_width();
  const size_t height = image->get_height();
  const size_t segment_width = width / nsegments;
  const size_t segment_height = height / nsegments;
  for(size_t x = 0; x < nsegments; x++)
    for(size_t y = 0; y < nsegments; y++){
      concatinated_histograms = concatinated_histograms + 
	createHistogram(image, 
			x * segment_width, width, 
			y * segment_height, height);
    }
  return concatinated_histograms;
}



Descriptor TrueClusterHistogram::createHistogram(MyImage *image, 
				      size_t x_start, size_t width, 
				      size_t y_start, size_t height){
  typedef Descriptor::iterator descit;

  Descriptor histogram(ncenters);
  bool first = true;
  // sliding window over the image
  for(int x = x_start; x + patch_size < width; x += spacing)
    for(int y = y_start; y + patch_size < height; y += spacing){  
      patch current_descriptor;
      { 
	// get patch descriptor
	Magick::Image newim = *image->getMagickImage(); 
	newim.crop(Magick::Geometry(patch_size, patch_size, x, y));
	MyImage subImage(newim);
	Parameters::push(parameters);
	current_descriptor = feature->extract(&subImage);
	Parameters::pop();
      }
      // change histogram according to descriptor and centers
      addToHistogram(current_descriptor, histogram, first);
      first = false;
    }
  return histogram;
}

void TrueClusterHistogram::addToHistogram(const patch &descriptor,
					     Descriptor &histogram,
					     bool first){
  switch(histogram_type){
  case 0: hbof(descriptor, histogram, first); break;
    //case 1: SOFT(descriptor, histogram, first); break;
  case 2: min(descriptor, histogram, first); break;
  }
}

void TrueClusterHistogram::hbof(const patch &descriptor,
				  Descriptor &histogram,
				  bool histogram_first){
  typedef patch_collection::const_iterator pcit;
  typedef Descriptor::iterator dcit;

  // find closest cluster
  size_t classification = 0;
  float min_distance = 0;
  bool first = true;
  for(pcit i = centers.begin(); i != centers.end(); ++i){
    float current_distance = (*i).distance(descriptor);
    if(first == true || current_distance < min_distance){
      min_distance = current_distance;
      classification = i - centers.begin();
    }
    first = false; 
  }

  // initialize histogram if applicable
  if(histogram_first)
    for(dcit i = histogram.begin(); i != histogram.end(); ++i)
      *i  = 0;
  // increment closest center in the histogram
  histogram[classification] += 1;
}

void TrueClusterHistogram::min(const patch &descriptor,
				  Descriptor &histogram,
				  bool first){
	Descriptor::iterator h = histogram.begin();
	patch_collection::iterator c = centers.begin();
	while(h != histogram.end() && c != centers.end()){
	  float dist = descriptor.distance(*c);
	  if(first || dist < *h)
	    *h = dist;
	  h++;
	  c++;
	}
}

void TrueClusterHistogram::save(string location){
    clustering::KMeansClustering().writeClusters(centers, 
						 location);
}


}} // namespaces
