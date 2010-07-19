#include "kmeansclustering.h"

using std::vector;
using std::endl;
using std::cout;

namespace vito{
namespace clustering{

//typedef KMeansClustering::patch patch;
//typedef KMeansClustering::labels labels;
//typedef KMeansClustering::patch_collection patch_collection;
//typedef KMeansClustering::label_collection label_collection;

patch_collection KMeansClustering::initialize_means(const int kmeans, 
						    const patch_collection &patches){
  srand(time(NULL));
  labels means_indices;
  while ((int) means_indices.size() < kmeans){
    int rand_index = rand() % patches.size() + 1;
    bool add = true;
    for(size_t i = 0; i < means_indices.size(); i++)
      if(means_indices[i] == rand_index)
	add = false;
    if(add)
      means_indices.push_back(rand_index);
  }
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
  for(size_t i = 0; i < a.size(); i++){
    total_distance += fabs(a[i] - b[i]);
  }
  return total_distance;
}

float KMeansClustering::total_distance_to_centers(const patch_collection &centers, 
						  const patch_collection &patches){
  float total = 0.0;
  for(size_t i = 0; i < patches.size(); i++){
    float smallest = -1.0;
    for(size_t j = 0; j < centers.size(); j++){
      const float current_distance = 
	KMeansClustering::distance(centers[j], patches[i]);
      //cout << i <<  " " << j << " " << current_distance << endl;
      if(smallest == -1 || current_distance < smallest)
	smallest = current_distance;
    }
    total += smallest;
  }
  return total / (float) patches.size();
}

patch_collection KMeansClustering::cluster(const patch_collection &patches){
  const int kmeans = 50;
  cout << "clustering into " << kmeans << " means" << endl;
  cout << "initializing means...";
  patch_collection cluster_centers = initialize_means(kmeans, patches);
  cout << "..done!" << endl;
  float distance_ = 1.0;
  bool stop = false;
  cout << "beginning updates..." << endl;
  while(distance_ > 0 && !stop){ // cluster until convergence
    float old_distance = distance_;
    distance_ = 0.0;
    cout << "+";
    patch_collection new_centers = update(cluster_centers, patches);
    for(size_t j = 0; j < cluster_centers.size(); j++){
      cout << ".";
      float p_dist = KMeansClustering::distance(cluster_centers[j], new_centers[j]);
      distance_ += p_dist;
    }
    cout << " total distance to centers: " << total_distance_to_centers(new_centers, patches) << endl;

    cout << "converging... distance now: " << distance_ << endl;
    cluster_centers = new_centers;
    if(old_distance == distance_)
      stop = true;
  }
  return cluster_centers;
}




}}
