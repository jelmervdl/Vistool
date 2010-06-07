#include "kmeansclustering.h"

using std::vector;
using std::endl;
using std::cout;

namespace vito{
namespace clustering{

typedef KMeansClustering::patch patch;
typedef KMeansClustering::labels labels;
typedef KMeansClustering::patch_collection patch_collection;
typedef KMeansClustering::label_collection label_collection;

patch_collection KMeansClustering::initialize_means(const int kmeans, 
						    const patch_collection &patches){
  srand(time(NULL));
  cout << rand() << " " << rand() << " " << rand() << endl;
  labels means_indices;
  while ((int) means_indices.size() < kmeans){
    int rand_index = rand() % patches.size() + 1;
    bool add = true;
    for(size_t i = 0; i < means_indices.size(); i++)
      if(means_indices[i] == rand_index)
	add = false;
    if(add)
      means_indices.push_back(rand_index);
    cout << std::rand()  << endl;
  }
  for(size_t i = 0; i < means_indices.size(); i++)
    cout << means_indices[i] << " ";
  cout << endl;

  patch_collection ret(kmeans);
  for(size_t i = 0; i < means_indices.size(); i++)
    ret[i] = patches[means_indices[i]];
  return ret;
}

label_collection KMeansClustering::classify_per_class(const patch_collection &cluster_centers,
						      const patch_collection &patches){
  label_collection patch_to_cluster_map(cluster_centers.size());
  for(size_t i = 0; i < patches.size(); i++){
    const patch &current_patch = patches[i]; 
    float smallest_distance = -1;
    int closest_cluster = -1;
    for(size_t j = 0; j < cluster_centers.size(); j++){
      const patch &cluster_center = cluster_centers[j];
      const float distance = KMeansClustering::distance(current_patch, cluster_center);
      if(distance < smallest_distance || smallest_distance == -1){
	smallest_distance = distance;
	closest_cluster = j;
      }
    }
    //cout << i << " -> " << closest_cluster << endl;
    patch_to_cluster_map[closest_cluster].push_back(i);    
  }
  return patch_to_cluster_map;
}

labels KMeansClustering::classify_per_patch(const patch_collection &cluster_centers,
							      const patch_collection &patches){
  labels classification(patches.size());
  for(size_t i = 0; i < patches.size(); i++){
    const patch &current_patch = patches[i]; 
    float smallest_distance = -1;
    int closest_cluster = -1;
    for(size_t j = 0; j < cluster_centers.size(); j++){
      const patch &cluster_center = cluster_centers[j];
      const float distance = KMeansClustering::distance(current_patch, cluster_center);
      if(distance < smallest_distance || smallest_distance == -1){
	smallest_distance = distance;
	closest_cluster = j;
      }
    }
    classification[i] = closest_cluster;    
  }
  return classification;
}


patch_collection KMeansClustering::update(const patch_collection &cluster_centers, 
					  const patch_collection &patches){
  label_collection patch_to_cluster_map =  classify_per_class(cluster_centers, patches);
  patch_collection new_cluster_centers(cluster_centers.size());
  //for every new cluster
  for(size_t i = 0; i <  cluster_centers.size(); ++i){
    patch &new_cluster_center = new_cluster_centers[i];
    new_cluster_center.resize(patches[0].size());
    const labels &indices = patch_to_cluster_map[i];
    //for every patch clustered into that cluster
    for(size_t j = 0; j < indices.size(); j++){
      const patch &descriptor = patches[indices[j]];
      // for each value
      for(size_t k = 0; k < descriptor.size(); k++){
	new_cluster_center[k] += descriptor[k];
      }
    }
    for(size_t k = 0; k < new_cluster_center.size(); k++){
      if(indices.size() > 0)
	new_cluster_center[k] /= indices.size();
    }
  }


  return new_cluster_centers;
}

float KMeansClustering::distance(const patch &a, const patch &b){
  assert(a.size() == b.size());
  float total_distance = 0.0;
  float aval, bval, before;
  for(size_t i = 0; i < a.size(); i++){
    aval = a[i];
    bval = b[i];
    before = total_distance;
    total_distance += fabs(a[i] - b[i]);
  }
  return total_distance;
}

patch_collection KMeansClustering::cluster(const patch_collection &patches){
  const int kmeans = 50;
  cout << "clustering into " << kmeans << " means" << endl;
  patch_collection cluster_centers = initialize_means(kmeans, patches);
  float distance_ = 1.0;
  while(distance_ > 0){ // cluster until convergence
    distance_ = 0.0;
    patch_collection new_centers = update(cluster_centers, patches);
    for(size_t j = 0; j < cluster_centers.size(); j++){
      float p_dist = KMeansClustering::distance(cluster_centers[j], new_centers[j]);
      distance_ += p_dist;
    }
    cout << "converging... distance now: " << distance_ << endl;
    cluster_centers = new_centers;
  }
  return cluster_centers;
}


}}
