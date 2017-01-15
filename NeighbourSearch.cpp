#include "NeighbourSearch.h"
#include <vector>

int i = 0;

void RangeNeighbourSearchA(string name, int radius, Hashtable *Hashtable, string temp,int k, int L, string method, int counter, char *tmp1, ofstream &outputFile, vector <string> &neighbour, DistanceMatrix *distancematrix)
{
    string item;
    if (method == "@metric_space hamming")
    {
        Hamming hamming(temp,name, item, 0.0);
        string g = hamming.ConstructGFunction(k);
        Hashtable->SearchBucketA(0, g, temp, name, 0, NULL, -1, method, radius, outputFile, 1, neighbour, 0);
    }
    else if (method == "@metric_space cosine")
    {
        CosineSim cosine(temp, name, item, 0.0);
        string g = cosine.ConstructGFunctionC(k);
        //cout << "g" << g << endl;
        Hashtable->SearchBucketA(0, g, temp, name,  0, NULL, -1, method, radius, outputFile, 1, neighbour, 0);
        //cout << "after hash search" << endl;
    }    
    else if (method == "@metric_space euclidean")
    {
        Euclidean euclidean(temp, name, item, 0.0);
        int fi = euclidean.ConstructFiFunctionC(L, k);
        Hashtable->SearchBucketA(0, "", temp, name,  0, NULL, fi, method, radius, outputFile, 1, neighbour, 0);
    }     
    else
    {
        //DistanceMatrix distancematrix(tmp1, counter, k);
        for (int i = 0; i < counter; i++) {
            outputFile << "Query:   item_idS" << i + 1 << endl;
            outputFile << "R-near neighbors:" << endl;
            string g = distancematrix->ConstructGFunction(i, k); //g function=concatenation of random h
            name = distancematrix->getName();
            int *row = distancematrix->getRow(i);
            Hashtable->SearchBucketA(0, g, temp, name, distancematrix->getNumOfRecors(), row, -1, method, radius, outputFile, 1, neighbour, distancematrix->getNumOfColumns());
        }

    }
}

void RangeNeighbourSearchB(string name, int radius, Hashtable *Hashtable, string temp,int k, int L, string method, int counter, char *tmp1, ofstream &outputFile, string &neighbour, DistanceMatrix *distancematrix, Cluster **centroid, int cluster)
{
    string item;
    if (method == "@metric_space hamming")
    {
        Hamming hamming(temp,name, item, 0.0);
        string g = hamming.ConstructGFunction(k);
        Hashtable->SearchBucketB(0, g, temp, name, 0, NULL, -1, method, radius, outputFile, 1, neighbour, 0, centroid, cluster);
    }
    else if (method == "@metric cosine")
    {
        CosineSim cosine(temp, name, item, 0.0);
        string g = cosine.ConstructGFunctionC(k);
        Hashtable->SearchBucketB(0, g, temp, name,  0, NULL, -1, method, radius, outputFile, 1, neighbour, 0, centroid, cluster);
    }    
    else if (method == "@metric euclidean")
    {
        Euclidean euclidean(temp, name, item, 0.0);
        int fi = euclidean.ConstructFiFunctionC(L, k);
        Hashtable->SearchBucketB(0, "", temp, name,  0, NULL, fi, method, radius, outputFile, 1, neighbour, 0, centroid, cluster);
    }     
    else
    {
        //DistanceMatrix distancematrix(tmp1, counter, k);
        for (int i = 0; i < counter; i++)
        {                 
            outputFile << "Query:   item_idS" << i+1 << endl;
            outputFile << "R-near neighbors:" << endl;
            string g = distancematrix->ConstructGFunction(i, k) ;     //g function=concatenation of random h
            name = distancematrix->getName();
            int *row = distancematrix->getRow(i);
            Hashtable->SearchBucketB(0, g, temp, name, distancematrix->getNumOfRecors(), row, -1, method, radius, outputFile, 1, neighbour, distancematrix->getNumOfColumns(), centroid, cluster);
        } 
            
    }
}


int Nearest_Neighbor_SearchB(string name, int radius, Hashtable *Hashtable, string temp,int k, int L, string method, int counter, char *tmp1, ofstream &outputFile, string &neighbour)
{
    string item;
    int distance = 0;
    if (method == "@metric_space hamming")
    {
        Hamming hamming(temp,name, item, 0.0);
        string g = hamming.ConstructGFunction(k);
        distance = Hashtable->SearchBucketB(L, g, temp, name,  0, NULL, -1, method, radius, outputFile, 2, neighbour, 0, NULL, 0);
    }
    else if (method == "@metric_space cosine")
    {
        CosineSim cosine(temp, name, item, 0.0);
        string g = cosine.ConstructGFunctionC(k);
        distance = Hashtable->SearchBucketB(L, g, temp, name, 0, NULL, -1, method, radius, outputFile, 2, neighbour, 0, NULL, 0);
    }    
    else if (method == "@metric_space euclidean")
    {
        Euclidean euclidean(temp, name, item, 0.0);
        int fi = euclidean.ConstructFiFunctionC(L, k);
        distance = Hashtable->SearchBucketB(L,"", temp, name, 0, NULL, fi, method, radius, outputFile, 2, neighbour, 0, NULL, 0);
    }     
    else
    {
        DistanceMatrix distancematrix(tmp1, counter, k);
        for (int i = 0; i < distancematrix.getNumOfRecors(); i++)
        {                 
            string g = distancematrix.ConstructGFunction(i, k) ;     //g function=concatenation of random h
            distance = Hashtable->SearchBucketB(L, g, temp, name, counter, NULL, -1, method, radius, outputFile, 2, neighbour, 0, NULL, 0);
        }
    }
    return distance;
}
