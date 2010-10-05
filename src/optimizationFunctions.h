#ifndef OPTIMIZATATIONFUNCTIONS_H
#define OPTIMIZATATIONFUNCTIONS_H

#include "experiment.h"
#include "parameters.h"
#include "dataset.h"
#include "svmclassifier.h"
#include "oneClassSVM.h"
#include "evaluation.h"

namespace vito{
namespace optimization{

float evaluateSVM();
float evaluateOneClassSVM();
float evaluateSVMAbdullah();

}}


#endif
