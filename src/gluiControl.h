#ifndef GLUICONTROL_H
#define GLUICONTROL_H

#include "toolState.h"
#include "gluiLoad.h"
#include "gluiFeatures.h"
#include "gluiEvaluate.h"
#include "classification.h"
#include "featureSelectionWindow.h"

namespace vito{
namespace gui{

void cluster();
void initGlui();
void nextPage();
void selectAndShow();
void createClassifierSelectButton();

}}

#endif
