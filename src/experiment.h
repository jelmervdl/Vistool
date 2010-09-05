#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "featureExtractor.h"
#include "classification.h"
#include "evaluation.h"
#include "statistics.h"

namespace vito{
namespace experiment{

void performExperiment(const std::string str, const int repetitions = 1);

float abdullah2010();


}}

#endif
