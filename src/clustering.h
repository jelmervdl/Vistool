#ifndef CLUSTERING_H
#define CLUSTERING_H

#include <assert.h>
#include <iostream>
#include <vector>
#include <string>
#include "descriptorWriter.h"

namespace vito{
namespace clustering{

typedef std::vector<float>  patch;
typedef std::vector<patch> patch_collection;

typedef std::vector<int>    labels;
typedef std::vector<labels> label_collection;

class ClusteringAlgorithm{
public:
  int              assertSamePatchLength(const patch_collection &c);
  void             writeClusters(const patch_collection &centers, 
				 std::string filename = "clusters.bin" );
  patch_collection readClusters(std::string file = "clusters.bin");

};

}}
#endif
