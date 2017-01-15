#include "Hashtable.h"
#include "Hamming.h"
#include <vector>

Hashtable::Hashtable(string temp, int k, int tablesize) //Hashtable Constructor
{
    name = temp;
    if (tablesize == 0) length = pow(2.0, k);   //Length for Hamming,Cosine and DistanceMatrix
    else length = tablesize / 8;               //Length for Euclidean
    array = new LinkedList[ length ];
}

Hashtable::Hashtable(const Hashtable& orig) {
}

Hashtable::~Hashtable() 
{
    delete [] array;
}


void Hashtable::InsertIntoHashtable(string temp, Hamming *HammingPoint, CosineSim *CosinePoint,Euclidean *EuclideanPoint,int *Row, int fi)
{    
    if (fi == -1)       //Insert for Hamming,Cosine and DistanceMatrix
    {
        const char *point = temp.c_str();
        int index = strtol(point, NULL, 2); 
        array[index].insertPoint(HammingPoint, CosinePoint, EuclideanPoint, Row);
    }
    else{       //Insert for Euclidean
        array[fi].insertPoint(HammingPoint, CosinePoint, EuclideanPoint, Row);
    }
}

int Hashtable:: SearchBucketA(int L, string temp, string temp1, string item, int counter, int *Row, int fi, string method, int radius, ofstream& file, int func, vector <string> &neighbour, int columns)
{
    int distance = 0;
    //string neighbor;
    if (fi == -1)       //SearchBucket for Hamming,Cosine and DistanceMatrix
    {
        const char *point = temp.c_str();
        int index = strtol(point, NULL, 2); 
        array[index].SearchA(radius, temp1, item, counter, Row, method, file, columns, neighbour);
    }
    else{    //SearchBucket for Euclidean
        array[fi].SearchA(radius, temp1, item, counter, Row, method, file, 0, neighbour);
        
    }
    return distance;
}

int Hashtable:: SearchBucketB(int L, string temp, string temp1, string item, int counter, int *Row, int fi, string method, int radius, ofstream& file, int func, string &neighbour, int columns, Cluster ** centroid, int cluster)
{
    int distance = 0;
    //string neighbor;
    if (fi == -1)       //SearchBucket for Hamming,Cosine and DistanceMatrix
    {
        const char *point = temp.c_str();
        int index = strtol(point, NULL, 2); 
        if (func == 1) array[index].SearchB(radius, temp1, item, counter, Row, method, file, columns, centroid, cluster);
        else        //SearchBucket for Euclidean
        {
            neighbour = array[index].NN_Search(L, radius, temp1, item,  NULL, Row, method, distance);
            //file << "NN found   " <<  neighbor << endl;
        }
    }
    else{
        if (func == 1)  array[fi].SearchB(radius, temp1, item, counter, Row, method, file, 0, centroid, cluster);
        else
        {            
            neighbour = array[fi].NN_Search(L, radius, temp1, item,  NULL, Row, method, distance);
            //file << "NN found   " << neighbor << endl;
        }
    }
    return distance;
}


void Hashtable::printTable(string method, int counter)
{
    //cout << length;
    cout << "\nHash Table:\n";   
    for (int i = 0; i < length; i++)
    {
        cout << "\nBucket " << i << ": ";
        array[i].printList(method, counter);
    }
}

int Hashtable::getLength()
{
    return length;
}

void Hashtable:: Assign(Cluster **cluster, string method, int k)
{
    for (int i = 0; i < length; i++)
    {        
        array[i].AssignCluster(cluster,  method, k);
    }
}

void Hashtable:: ClusterAssign(Cluster **cluster, string method, int k)
{
    for (int i = 0; i < length; i++)
    {        
        array[i].CreateRealCluster(cluster, method, k);
    }
}