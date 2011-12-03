#ifndef RAWFEATURE_H
#define RAWFEATURE_H

#include "singleton.h"
#include "feature.h"
#include "myImage.h"

namespace vito{
namespace features{

class RawFeature : public Feature, public Singleton<RawFeature>
{
	friend class Singleton<RawFeature>;

public:
	~RawFeature();

	// return activity of feature
	bool isActive();

	// extract actual descriptor;
	Descriptor extract_(MyImage *image, bool saveVisualRepresentation, Magick::Image* image);

	virtual std::string getParameterName();
};

} } // end namespace

#endif
