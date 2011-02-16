#include "patchExtractor.h"

using std::vector;
using std::cout;
using std::endl;

namespace vito { 
namespace clustering {

using features::Feature;

patch_collection PatchExtractor::getPatches (DataPoint dp, 
					     Feature *feature){
  DataPointCollection dps;
  dps.push_back(dp);
  return getPatches(dps, feature);
}
                    

                              
patch_collection PatchExtractor::getPatches (const DataPointCollection &dps, 
					     Feature *feature){
  patch_collection all_patches;
  Parameters *parameters = Parameters::getInstance();
  const int bins = parameters->getiParameter("clustering_patches");
  typedef vector<DataPoint>::const_iterator dp_it;

  for(dp_it i = dps.begin(); i != dps.end(); ++i){
    cout << "getting image: " << i->get_image_url() << endl;
    MyImage i_image(i->get_image_url());
    patch_collection i_patches = getPatches(i_image, feature, bins);
    all_patches.insert(all_patches.end(), i_patches.begin(), i_patches.end());
  }
  return all_patches;
}



patch_collection PatchExtractor::getPatches (MyImage &myImage, 
					     Feature *feature, 
					     int bins){
  
  Parameters *parameters = Parameters::getInstance();

  // resize magick image if warp is on
  if(parameters->getiParameter("clustering_warp_image") > 0){
    const int width  = parameters->getiParameter("clustering_warp_x");
    const int height = parameters->getiParameter("clustering_warp_y");
    Magick::Image magick = *myImage.getMagickImage();
    cout << "is: " << magick.columns() << "x"
	 << magick.rows() << " "  << width << " x " << height << "?";
    if( (int) magick.columns() != width || 
        (int) magick.rows()    != height   ){
      std::stringstream ss;
      ss << width <<"x" << height << "!";
      magick.transform(Magick::Geometry(ss.str()));
      MyImage resized_Image(magick);
      return getPatches(resized_Image, feature, bins);
    }
  }
  
  if(bins == 0) 
    bins = parameters->getiParameter("clustering_patches");

  // retrieve patches for each bin
  patch_collection patches;    
  for(int x = 0; x < bins; x++){
      for(int y = 0; y < bins; y++){
	MyImage subImage(myImage.getMagickSubImage(x, bins, y, bins));
	patch current_patch = getPatch(&subImage, feature);
	patches.push_back(current_patch);
      }
  }
   return patches;
}



patch PatchExtractor::getPatch (MyImage *image, 
				Feature *feature){
  return feature->extract(image);
}

}}
