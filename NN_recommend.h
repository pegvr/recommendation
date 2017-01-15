#ifndef NN_RECOMMEND_H
#define	NN_RECOMMEND_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "CosineSim.h"
#include "Euclidean.h"
#include "Hamming.h"
#include "DistanceMatrix.h"
#include "Hashtable.h"


Hashtable ** CreateHash(int L, int k, int tablesize);
void NNRMDA(int k, int N, string method, vector <string> neighbours, int P, int items, Hamming *HammingPoint, CosineSim *CosinePoint,Euclidean *EuclideanPoint, ofstream &outputFile);

void NNRMDB(int k, int N, string method, Cluster **cluster, int items, Hamming **HammingPoint, CosineSim **CosinePoint,Euclidean **EuclideanPoint, ofstream &outputFile);


#endif	/* NN_RECOMMEND_H */

