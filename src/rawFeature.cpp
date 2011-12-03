#include "rawFeature.h"

namespace vito{
namespace features{

const int COLORS_GRAYSCALE = 1;
const int COLORS_RGB = 3;

RawFeature::~RawFeature()
{
  // intentionally left empty
}

std::string RawFeature::getParameterName()
{
  return "raw_pixels";
}

bool RawFeature::isActive()
{
  return Parameters::getInstance()->getiParameter("feature_raw_pixels") > 0;
}

Descriptor RawFeature::extract_(MyImage *image, bool saveVisualRepresentation, Magick::Image *canvas)
{
  size_t cols = image->getMagickImage()->columns();
  size_t rows = image->getMagickImage()->rows();

  int colors = Parameters::getInstance()->getiParameter("raw_pixels_grayscale") > 0
    ? COLORS_GRAYSCALE
    : COLORS_RGB;

  Magick::PixelPacket const *pixels =
    Magick::Pixels(*(image->getMagickImage())).getConst(0, 0, cols, rows);
  
  Descriptor data;
  data.reserve(cols + rows + colors);

  for (size_t i = 0; i < cols + rows; ++i)
  {
    switch (colors)
    {
      case COLORS_GRAYSCALE:
        data.push_back(pixels[i].red + pixels[i].green + pixels[i].blue);
        break;
      
      case COLORS_RGB:
      default:
        data.push_back(pixels[i].red);
        data.push_back(pixels[i].green);
        data.push_back(pixels[i].blue);
        break;
    }
  }

  data.normalize();
  return data;
}

}}
