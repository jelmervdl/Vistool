#ifndef OPTIMIZATATIONFUNCTIONS_H
#define OPTIMIZATATIONFUNCTIONS_H

#include "parameters.h"
#include "dataset.h"
#include "SVMClassifier.h"
#include "oneClassSVM.h"
#include "evaluation.h"

namespace vito{
namespace optimization{

float evaluateSVM();
float evaluateOneClassSVM();

}}


#endif
