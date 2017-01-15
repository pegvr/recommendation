/* 
 * File:   alaLloyds.h
 * Author: angelique
 *
 * Created on November 22, 2016, 9:41 PM
 */

#ifndef ALALLOYDS_H
#define	ALALLOYDS_H
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "Cluster.h"
#include "Distances.h"
#include "PAM.h"

void alalloyds(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int *objectivefunction, float * ObjectiveFunctionF);


#endif	/* ALALLOYDS_H */

