# Vistool 

# Running experiments (cli)

	./machineVisionTool experiment CLASSIFIER DATASET

Experiments consist of a dataset and a classifier to test. Datasets can be defined in `datasets/index.xml`. Possible classifiers are _svm_ and _nn_. The parameters for these as well as the feature extractor and its accompanying parameters are found in `parameters.xml`.

The experiment if performed in `src/experiment.cpp`, `float performExperiment(classifier, dataset-name, repetitions, kDataPoints)`.