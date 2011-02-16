#ifndef MAIN_H
#define MAIN_H

#include "boost/thread/thread.hpp"

//test environment
#include "test.h"

//vision tool
#include "gluiVisionTool.h"

// parameter optimization
#include "parameterOptimization.h"
#include "optimizationFunctions.h"

//classifiers
#include "segmentSVM.h"
#include "oneClassSVM.h"

#include "kmeansclustering.h"

#include <locale>
#include <iomanip>

#include "mpeg7.h"
#include "patchExtractor.h"
#include "kmeanshistogram.h"

#include "classifierStack.h"
#include "experiment.h"

#include "clusterFeatureExtractor.h"

void stack_function();
void test_threads();
void cluster(std::string filename);
void printLibraries();
void one_class_test();
void one_class_test2();
void testClassifierStack();

#endif

