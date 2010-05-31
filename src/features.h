#ifndef FEATURES_H
#define FEATURES_H

#include <vector>
#include "feature.h"
#include "mpeg7.h"
#include "sift.h"
#include "histogram.h"

namespace vito{
namespace features{



std::vector<Feature*> getExistingFeatures();
std::vector<Feature*> getActiveFeatures();

}}

#endif
