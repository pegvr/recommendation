#ifndef HASHTABLE_H
#define	HASHTABLE_H
#include "LinkedList.h"
#include <math.h>

class Hashtable {
public:
    Hashtable(string temp, int k, int tablesize);
    Hashtable(const Hashtable& orig);
    virtual ~Hashtable();
    
    // Adds an item to the Hash Table.
    void insertPoint( Point * newPoint );
       
    // Display the contents of the Hash Table to console window.
    void printTable(string method, int counter);
  
    // Returns the number of locations in the Hash Table.
    int getLength();
    
    // Returns the number of Points in the Hash Table.
    int getNumberOfPoints();
    void InsertIntoHashtable(string temp, Hamming *HammingPoint, CosineSim *CosinePoint,Euclidean *EuclideanPoint, int *Row, int fi);
    int SearchBucketA(int L, string temp, string temp1, string item, int counter, int *Row, int fi, string method, int radius, ofstream& file, int func, vector <string> &neighbour, int columns);
    int SearchBucketB(int L, string temp, string temp1, string item, int counter, int *Row, int fi, string method, int radius, ofstream& file, int func, string &neighbour, int columns, Cluster ** centroid, int cluster);
    void Assign(Cluster **cluster, string method,int k);
    void ClusterAssign(Cluster **cluster, string method, int k);
private:
    // Array is a reference to an array of Linked Lists.
    string name;
    LinkedList * array;
    
    // Length is the size of the Hash Table array.
    int length;
    
};
#endif

