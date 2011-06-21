#ifndef CLUSTERING_H
#define CLUSTERING_H

#include "descriptor.h"
#include "descriptorWriter.h"

namespace vito{
namespace clustering{

// Descriptors for patches are called patches
typedef Descriptor  patch;
typedef std::vector<Descriptor> patch_collection;

typedef std::vector<int>    labels;
typedef std::vector<labels> label_collection;

class ClusteringAlgorithm{
public:
  int              assertSamePatchLength(const patch_collection &c);

  //write clusters to file
  void             writeClusters(const patch_collection &centers, 
				 std::string filename = "clusters.bin" );

  // read clusters from a file
  patch_collection readClusters(std::string file = "clusters.bin");

};

}}
#endif
