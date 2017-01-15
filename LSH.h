#ifndef LSH_H
#define LSH_H

#include <vector>
#include <cstdlib>
#include <string>
#include <time.h>
#include "Cluster.h"
#include "Distances.h"
#include "Hamming.h"
#include "CosineSim.h"
#include "DistanceMatrix.h"
#include "Euclidean.h"
#include "NeighbourSearch.h"
#include "Hashtable.h"
#endif /* LSH_H */

void LSH(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int NumofHashFUnctions, int L, int choice);

