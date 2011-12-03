#ifndef FEATURES_H
#define FEATURES_H

#include "mpeg7.h"
#include "facedetect.h"
#include "sift.h"
#include "histogram.h"
#include "classifierStack.h"

namespace vito{
namespace features{

// return all supported features
std::vector<Feature*> getExistingFeatures();
// return all currently active features according to current parameters.
std::vector<Feature*> getActiveFeatures();
// print the active features
void                  printActiveFeatures();

}
}

#endif
