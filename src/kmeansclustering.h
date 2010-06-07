#ifndef KMEANSCLUSTERING_H
#define KMEANSCLUSTERING_H

#include <math.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <assert.h>

#include "clustering.h"

namespace vito{
namespace clustering{

class KMeansClustering : public ClusteringAlgorithm{


public:
  label_collection classify_per_class(const patch_collection &cluster_centers,
				      const patch_collection &patches);

  labels           classify_per_patch(const patch_collection &cluster_centers,
				      const patch_collection &patches);

  patch_collection initialize_means(const int kmeans, 
				    const patch_collection &patches);

  patch_collection update(const patch_collection &cluster_centers, 
			  const patch_collection &patches);

  patch_collection cluster(const patch_collection &patches);

  float            distance(const patch &a, const  patch &b);
};

}}

#endif
