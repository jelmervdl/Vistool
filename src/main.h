#ifndef MAIN_H
#define MAIN_H

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


void printLibraries ();
void one_class_test();
void one_class_test2();

#endif

