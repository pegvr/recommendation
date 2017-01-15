#ifndef LINKEDLIST_H
#define	LINKEDLIST_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Hamming.h"
#include "CosineSim.h"
#include "Euclidean.h"
#include <math.h>
#include "Distances.h"
#include "Cluster.h"

struct Point
{
    Hamming *hamming_key;
    Euclidean *euclidean_key;
    CosineSim *cosine_key;
    int *row;
    int flag;
    Point * next;
    Point()
    {
        hamming_key = NULL;
        euclidean_key = NULL;
        cosine_key = NULL;
        row = NULL;
        next = NULL; 
        flag = -1;
    };
    Point(Hamming *HammingPoint, CosineSim *CosinePoint,Euclidean *EuclideanPoint, int *Row)
    {
        hamming_key = HammingPoint;
        euclidean_key = EuclideanPoint;
        cosine_key = CosinePoint;
        row = Row;
        next = NULL; 
        flag = -1;
    };
};

class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList& orig);
    virtual ~LinkedList();
    // Inserts an item at the end of the list.
    void insertPoint( Hamming * newPoint,CosineSim *CosinePoint,Euclidean *EuclideanPoint, int * Row);
    void SearchA(int radius, string temp,string item, int counter, int * Row, string method, ofstream& file, int columns, vector <string> &neighbours);    void printList(string method, int counter);
    void SearchB(int radius, string temp, string item, int counter, int * Row, string method, ofstream& file, int columns, Cluster ** cluster, int k);
    string NN_Search(int L,int radius, string temp,string item,Euclidean *EuclideanPoint, int * Row, string method, int &distance);
    void AssignCluster(Cluster **cluster, string method,int k);
    void CreateRealCluster(Cluster **cluster, string method, int k);
    // Returns the length of the list.
    int getLength();
private:
    Point * head;
    
    // Length is the number of data nodes.
    int length;
};

#endif	/* LINKEDLIST_H */

