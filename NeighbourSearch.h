#ifndef NEAREST_NEIGHBOR_H
#define NEAREST_NEIGHBOR_H


#include <string>
#include "Hamming.h"
#include "Hashtable.h"
#include "DistanceMatrix.h"
#include "Cluster.h"

void RangeNeighbourSearchA(string name, int radius, Hashtable *Hashtable, string temp,int k, int L, string method, int counter, char *tmp1, ofstream &outputFile, vector <string> &neighbour, DistanceMatrix *distancematrix);

void RangeNeighbourSearchB(string name, int radius, Hashtable *Hashtable, string temp,int k, int L, string method, int counter, char *tmp1, ofstream &outputFile, string &neighbour, DistanceMatrix *distancematrix, Cluster **centroid, int cluster);

int Nearest_Neighbor_SearchB(string name, int radius, Hashtable *Hashtable, string temp,int k, int L, string method, int counter, char *tmp1, ofstream &outputFile, string &neighbour);

#endif /* NEAREST_NEIGHBOR_H */

