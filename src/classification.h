#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include "toolState.h"
#include "svmclassifier.h"
#include "nnclassifier.h"
#include "segmentSVM.h"
#include "oneClassSVM.h"

namespace vito{
namespace classification{

// provide a list of all available classification algorithms
std::vector<Classifier*> getExistingClassifiers();

// provide the pointer to a certain classifier
Classifier              *getExistingClassifier(int i );
}}

#endif
