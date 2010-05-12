#ifndef FEATURES_H
#define FEATURES_H

#include "feature.h"
#include <vector>
#include "sift.h"
#include "histogram.h"

namespace vito{
namespace features{

std::vector<Feature*> getExistingFeatures();
std::vector<Feature*> getActiveFeatures();

}}

#endif
