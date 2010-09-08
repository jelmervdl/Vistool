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
Dataset getDataSet(const std::string str);
float performExperiment(const std::string str,
			const std::string dataset = "abdullah2010",
			const int repetitions = 1);
Dataset abdullah2010();
float svm( Dataset &dataset);
float clustering( Dataset &dataset);

}}

#endif
