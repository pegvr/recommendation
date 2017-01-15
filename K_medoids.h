/* 
 * File:   K_medoids.h
 * Author: angelique
 *
 * Created on November 21, 2016, 4:29 PM
 */

#ifndef K_MEDOIDS_H
#define	K_MEDOIDS_H
#include "Cluster.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include "Distances.h"

using namespace std;

void k_medoidspp(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance);


#endif	/* K_MEDOIDS_H */

