#include "clustering.h"
#include <cassert>

using std::string;
using std::cout;
using std::endl;
using std::vector;

namespace vito{
namespace clustering{

void ClusteringAlgorithm::writeClusters(const patch_collection &centers, 
					string file){
  const int kPatches = centers.size();
  const int patch_size = assertSamePatchLength(centers);
  vector<float> toFile(2 + kPatches * patch_size);
  toFile[0] = (float) kPatches;
  toFile[1] = (float) patch_size;
  for(int p = 0; p < kPatches; p++)
    for(int v = 0 ; v < patch_size; v++)
      toFile[2 + p * patch_size + v] = centers[p][v];
  write::writeDescriptor(&toFile, file);
}

int ClusteringAlgorithm::assertSamePatchLength(const patch_collection &c){
  int size = -1;
  for(size_t i = 0; i < c.size(); i++)
    if(size == -1)
      size = c[i].size();
    else
      assert(size == (int) c[i].size());
  return size;
}

patch_collection ClusteringAlgorithm::readClusters(string file){
  vector<float> values;
  write::readDescriptor(&values, file);
  assert(values.size() > 2);
  const int kPatches = values[0];
  const int patch_size = values[1];
  assert((int) values.size() == 2 + kPatches * patch_size);
  vector<Descriptor> centers(kPatches, vector<float>(patch_size));
  for(int p = 0; p < kPatches; p++)
    for(int v = 0; v < patch_size; v++)
      centers[p][v] = values[2 + p * patch_size + v];
  return centers;
}


}}
