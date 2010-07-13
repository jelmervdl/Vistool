#ifndef GLUICONTROL_H
#define GLUICONTROL_H

#include "featureWindow.h"
#include "toolState.h"
#include "gluiLoad.h"
#include "gluiFeatures.h"
#include "gluiEvaluate.h"
#include "classification.h"
#include "features.h"
#include "featureSelectionWindow.h"
#include "clusterFeatureExtractor.h"

namespace vito{
namespace gui{

void cluster();
void initGlui();
void nextPage();
void selectAndShow();
void createClassifierSelectButton();
void createFeatureSelectButton();
void createFeatureWindow();

}}

#endif
