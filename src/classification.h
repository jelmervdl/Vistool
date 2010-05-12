#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include "toolState.h"
#include <vector>
#include "svmclassifier.h"
#include "nnclassifier.h"
#include "segmentSVM.h"
#include "oneClassSVM.h"

namespace vito{
namespace classification{

std::vector<Classifier*> getExistingClassifiers();
Classifier              *getExistingClassifier(int i );
}}

#endif
