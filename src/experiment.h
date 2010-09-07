#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "featureExtractor.h"
#include "classification.h"
#include "evaluation.h"
#include "statistics.h"
#include "kmeanshistogram.h"

namespace vito{
namespace experiment{

Dataset abdullah2010DataSet();

float performExperiment(const std::string str, const int repetitions = 1);
float abdullah2010();
float clustering();

}}

#endif
