#ifndef KMEANSCLUSTERING_H
#define KMEANSCLUSTERING_H

#include "descriptor.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <assert.h>
#include "clustering.h"
#include "parameters.h"

// Kmeans Clustering Implementation using the summed (unsquared)
// distance between patches.

namespace vito{
namespace clustering{

class KMeansClustering : public ClusteringAlgorithm{

public:
  // get a set of vectors containing the classifications of patches
  // towards a set of k-means
  label_collection classify_per_class(const patch_collection &cluster_centers,
				      const patch_collection &patches);

  // get the classification per class
  labels           classify_per_patch(const patch_collection &cluster_centers,
				    const patch_collection &patches,
				    Descriptor *histogram);

  // initialize means by picking a random set of patches as the
  // initial means
  patch_collection initialize_means(const int kmeans, 
				    const patch_collection &patches);

  // update function converging the kmeans toward the ideal cluster
  // centers
  patch_collection update(const patch_collection &cluster_centers, 
			  const patch_collection &patches);

  // excecute the entire clustering pipeline given a set of initial
  // patches
  patch_collection cluster(const patch_collection &patches);

  // find the distance between two patches
  float            distance(const patch &a, const  patch &b);

  float            total_distance_to_centers(const patch_collection &centers, 
					     const patch_collection &patches);
};

}}

#endif
