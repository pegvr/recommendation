/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "LSH.h"



Hashtable ** CreateHash(int L, int k, int tablesize);
void QuerySearch(Cluster **cluster, Hashtable **PointersToHashtable, int L, int k, string method, int counter,int NumofHashFUnctions);

Hashtable **PointersToHashtable;

void LSH(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int NumofHashFUnctions, int L, int choice)
{ 
    string g;
    if (method == "@metric_space hamming")
    {  
        if (choice == 4)
        {
            PointersToHashtable = CreateHash(L, NumofHashFUnctions , 0); //Construct L HashTables
            for(int j = 0; j < N; j++)
            {
                for (int i = 0; i < L; i++)             //insert point into all hashtables
                {
                    g = hamming[j]->ConstructGFunction(NumofHashFUnctions); 
                    //cout << " i made it " << endl ; //g function = concatenation of random h
                    PointersToHashtable[i]->InsertIntoHashtable(g, hamming[j], NULL, NULL, NULL, -1); //Insert Hamming point into HasttableI
               }
            }
        }
        QuerySearch(cluster, PointersToHashtable,  L, k,  method, N, NumofHashFUnctions);
        PointersToHashtable[0]->ClusterAssign(cluster, method, k);
    }
    else if (method == "@metric euclidean")
    {
        Hashtable **PointersToHashtable = CreateHash(L, NumofHashFUnctions, N); 
        for(int j = 0; j < N; j++)
        {
            for (int i = 0; i < L; i++)             //insert point into all hashtables
            {
                int length = PointersToHashtable[i]->getLength();
                int fi = euclidean[j]->ConstructFiFunctionC(length, NumofHashFUnctions);      //Construct fi
                PointersToHashtable[i]->InsertIntoHashtable("", NULL, NULL, euclidean[j], NULL, fi);
            }
        }
        QuerySearch(cluster, PointersToHashtable,  L, k,  method, N, NumofHashFUnctions);
        PointersToHashtable[0]->ClusterAssign(cluster, method, k);
    }
    else if (method == "@metric cosine")
    {
        Hashtable **PointersToHashtable = CreateHash(L, NumofHashFUnctions, 0);   
        srand(time(0));
        for (int j = 0; j < N; j++)
        {
            for (int i = 0; i < L; i++)             //insert point into all hashtables
            {   
                g = cosine[j]->ConstructGFunctionC(NumofHashFUnctions);      //g function = concatenation of random h               
                PointersToHashtable[i]->InsertIntoHashtable(g, NULL, cosine[j], NULL, NULL, -1);    //Insert Cosine point into HashtableI
            }   
        }
        QuerySearch(cluster, PointersToHashtable,  L, k,  method, N, NumofHashFUnctions);
        PointersToHashtable[0]->ClusterAssign(cluster, method, k);
    }
    else
    {   
        Hashtable **PointersToHashtable = CreateHash(L, NumofHashFUnctions, 0);   //Construct L HashTable
        for ( int i = 0; i < distance->getNumOfRecors(); i++)
        {
            int *row = distance->getRow(i);       //Get row i of DistanceMatrix              
            for (int j = 0; j < L; j++)            //insert point into all hashtables
            {                   
                string g = distance->ConstructGFunction(i, NumofHashFUnctions);      //g function=concatenation of random h
                PointersToHashtable[j]->InsertIntoHashtable(g, NULL, NULL, NULL, row, -1); //Insert row -> point into the hashtabel
            }
        }
        
    }
    
}




Hashtable ** CreateHash(int L, int k, int tablesize)
{
    Hashtable **PointersToHashtable = new Hashtable*[L];  //Table which points to g1,g2,...,gl hashtables
    char temp1[10];
    string temp = "g0";
    for (int i = 0; i < L; i++)
    {                
        sprintf(temp1, "%d", i);        //Hashtable number
        temp = 'g' + temp1;
        PointersToHashtable[i] = new Hashtable (temp, k, tablesize);
    }
    return PointersToHashtable;
}

void QuerySearch(Cluster **cluster, Hashtable **PointersToHashtable, int L, int k, string method, int counter, int NumofHashFUnctions)
{
    string line, temp, temp1 = "cluster0", neighbour;
    int min, dist, min_dist,  * row, radius;
    float distf = 0, min_distf;
    char *tmp;
    for(int i = 0; i < k; i++)
    {
        min_dist = 100000;
        min_distf = 100000.0;
        for(int j = 0; j < k; j++)
        {
            if (method == "@metric_space hamming")
            {
                dist = DistanceHamming(cluster[j]->getCentroid(), cluster[i]->getCentroid());
                //cout << dist << endl; 
                                             
            }                
            else if (method == "@metric euclidean")
            {
                distf = DistanceEuclidean(cluster[i]->getCentroid(), cluster[j]->getCentroid());
            }
            else if (method == "@metric cosine")
            {

                distf = DistanceEuclidean(cluster[i]->getCentroid(), cluster[j]->getCentroid());
            }
            else
            {   
                int *row = cluster[i]->GetPointD(j);
                dist = row[j];
            }  
            if ((dist < min_dist && dist != 0) || (distf < min_distf && distf != 0))
            {
                min_dist = dist;
                cout << min_dist << "mindist" << endl;
                min_distf = distf;
            }  
            
        }
    }

    if (method == "@metric_space hamming")
    {radius = min_dist / 2;
    //cout << "yessss" << min_dist  << endl ; 
    //cout << "i made it 2" << endl ; 
    }
    else 
    {  
        //cout << min_distf << endl ; 
        radius = min_distf / 2;
        
    }
    //cout << radius << endl;
    ofstream outputFile("temp.txt");
    for(int z = 0; z < 5; z++)
    {
        for(int j = 0; j < k; j++)
        {
            min = 1000; 
            if (method != "@metric_space matrix")   temp = cluster[j]->getCentroid();
            else row = cluster[j]->getCentroidD();
            temp1 =  "cluster" + to_string(j);
            cout << "Query:   " << temp1 << endl;
            cout << "R-near neighbors:" << endl;
            for (int i = 0; i < L; i++)   //Search  neighbour within radius
            {
                if (method == "@metric_space matrix")
                {
                    //DistanceMatrix *distancematrix = new DistanceMatrix(tmp1, counter, k);
                    RangeNeighbourSearchB(temp1, radius, PointersToHashtable[i], temp, NumofHashFUnctions, L, method, counter, tmp, outputFile, neighbour, NULL, cluster, j);              
                }
                else
                {
                    //cout << "bhka vre" << endl; 
                    // DistanceMatrix distancematrix(tmp1, counter, k);
                    RangeNeighbourSearchB(temp1, radius, PointersToHashtable[i], temp, NumofHashFUnctions, L, method, counter, tmp, outputFile, neighbour, NULL, cluster, j);

                }
            }                                   
        }
        radius = radius * 2;
    }
    for (int i = 0; i < L; i++)   //Search  neighbour within radius
    {
        PointersToHashtable[i]->Assign(cluster, method, k);
    } 

}