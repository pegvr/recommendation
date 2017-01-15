#ifndef DATAPOINTS_H
#define	DATAPOINTS_H
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "Hamming.h"
#include "CosineSim.h"
#include "DistanceMatrix.h"
#include "Euclidean.h"

using namespace std;

Hamming ** CreateHammingPoints(int counter, char *tmp);
Euclidean ** CreateEuclideanPoints(int counter, char *tmp);
CosineSim ** CreateCosinePoints(int counter, char *tmp);
DistanceMatrix * CreateMatrixPoints(int counter, char *tmp, int k);

#endif	/* DATAPOINTS_H */

