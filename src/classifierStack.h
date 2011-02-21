#ifndef CLASSIFIERSTACK_H
#define CLASSIFIERSTACK_H

// #include <algorithm>
// #include <iostream>
// #include <iterator>
#include "featureExtractor.h"
#include "feature.h"
#include "classifier.h"
#include "svmclassifier.h"

namespace vito{
namespace features{


class Setup{
protected:
  int parameters;
  std::string previous;
  std::string name;
public:
  Setup(std::string xmlfile);
  void push();
  void pop();
  std::string get_name();
};

class SetupFeature : public Feature, public std::vector<Setup>{
public:
  SetupFeature(std::vector<Setup> setup);
  SetupFeature();
  virtual std::string        getParameterName();
  virtual bool               isActive();
  virtual Descriptor         extract_(MyImage *Image, 
				      bool makeVisualRepresentation, 
				      Magick::Image * representation); 
};

class NaiveStackFeatures : public std::vector<SetupFeature> , 
			   public Singleton<NaiveStackFeatures>{
public:
  void add_to(std::vector<Feature*> &features);
};

/* defines the setup of a classification pipeline, naming a set of
   features and a classifier */

class SVMActivationSetup : public Setup{
private:
  classification::SVMClassifier svm;
  std::string origin;
public:
  SVMActivationSetup(std::string setting);
  void train(DataPointCollection dps);
  Descriptor getActivation(DataPoint dp);
  std::string getFile();
};

class ClassifierSetup : public Setup, public Feature{
protected:
  classification::Classifier *classifier;
  int                         parameters;

public:
  ClassifierSetup(classification::Classifier *c);
  ClassifierSetup(classification::Classifier *c, 
		  std::string xmlfile);


  void                train(const ExampleCollection &descriptors);
  bool                isActive();
  std::string         getParameterName();
  virtual Descriptor  extract_(MyImage *Image, 
			       bool makevisres, 
			       Magick::Image *representation);
};

class SVMStack : public std::vector<features::SVMActivationSetup>,
		 public Feature{
public:
  virtual bool isActive();
  virtual std::string getParameterName();
  virtual Descriptor extract_(MyImage *Image,
			      bool makevisrep,
			      Magick::Image rep);
  void train(DataPointCollection dps);
};
}

namespace classification{
/*
class SVMStackClassifier : public Classifier{
 private:
  SVMClassifier svm;
  features::SVMStack *svmstack;
public:
*/

//doesn't work
class SVMStack : public std::vector<features::SVMActivationSetup>, 
		 public Classifier{
private:
  ExampleCollection getStackExamples(ExampleCollection &examples);
  SVMClassifier svm;
public:
  std::string          get_name();
  void                 train(const ExampleCollection &examples);
  Label                classify(const Descriptor &descriptor);
  ExampleCollection    getStackExamples(const ExampleCollection &examples);
  DescriptorCollection getStackResults(const DescriptorCollection & dc);
  Descriptor           getStackResults(const Descriptor &descriptor);
};


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
