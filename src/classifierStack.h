#ifndef CLASSIFIERSTACK_H
#define CLASSIFIERSTACK_H

// #include <algorithm>
// #include <iostream>
// #include <iterator>
#include "classifier.h"
#include "feature.h"

namespace vito{
namespace features{

/* defines the setup of a classification pipeline, naming a set of
   features and a classifier */
class ClassifierSetup : public Feature{
protected:
  classification::Classifier *classifier;
  int                         parameters;

public:
  ClassifierSetup(classification::Classifier *c);
  ClassifierSetup(classification::Classifier *c, 
		  std::string xmlfile);


  void        train(const ExampleCollection &descriptors);
  bool        isActive();
  std::string getParameterName();
  Descriptor  extract_(MyImage *Image, 
		       bool makevisres, 
		       Magick::Image *representation);
};

}

namespace classification{

/* defines a classifier Stack, using several ClassifierSetups to
   define the features and classification to be extracted which then
   serve as a feature to a stacked classifier */
class ClassifierStack : public Classifier {
protected:
  std::vector<features::ClassifierSetup> setups;
public:
  using Classifier::train;
  using Classifier::classify;

  ClassifierStack(std::vector<features::ClassifierSetup> s);
  ~ClassifierStack();

  std::string      get_name();
  int              classify(const Descriptor &descriptor);
  void             train(const ExampleCollection &files);

};

}

}

#endif
