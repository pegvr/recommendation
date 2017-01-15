#ifndef PAM_H
#define	PAM_H
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "Cluster.h"
#include "Distances.h"

using namespace std;

void PAM(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance,int * objectivefunction, float * ObjectiveFunctionF);
void PAM_Update(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int *objectivefunction, float * ObjectiveFunctionF);

#endif	/* PAM_H */

