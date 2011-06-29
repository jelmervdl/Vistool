#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "clusterFeatureExtractor.h"
#include "featureExtractor.h"
#include "classification.h"
#include "evaluation.h"
#include "statistics.h"
#include "kmeanshistogram.h"
#include "classification.h"
#include "trueClustering.h"

namespace vito{
namespace experiment{

Dataset abdullah2010DataSet();
Dataset getDataSet(const std::string str);
float   performExperiment(const std::string str,
			  const std::string dataset = "abdullah2010",
			  const int repetitions = 1,
			  const size_t kDataPoints = 30);
Dataset abdullah2010();
float   svm(Dataset &dataset, size_t datapoint = 30);
float   nn(Dataset &dataset, size_t datapoints = 30);
float   clustering( Dataset &dataset);
void cluster(std::string dataset, std::string filename);

}}

#endif
