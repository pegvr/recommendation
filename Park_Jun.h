#ifndef PARK_JUN_H
#define	PARK_JUN_H
#include "Cluster.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include "Distances.h"

using namespace std;
void ParkJun(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance);


#endif	/* PARK_JUN_H */

