#include "K_medoids.h"



void k_medoidspp(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance)
{
    int sum = 0, r = 0, dist, j; 
    float P[N], distf;
    
    /*Choose randomly first centroid*/
    int rand_num = (rand() / (RAND_MAX + 1.0))* N; 
    if (method == "@metric_space hamming")
        cluster[0] = new ClusterH(hamming[rand_num]);
    else if (method == "@metric euclidean")
        cluster[0] = new ClusterE(euclidean[rand_num]);
    else if (method == "@metric cosine")
        cluster[0] = new ClusterC(cosine[rand_num]);
    else
        cluster[0] = new ClusterD(distance->getRow(rand_num)); 

    for( int i = 0; i < k-1; i++) //for every other cluster
    {
        sum = 0;
        float sumf = 0.0;
        for ( j = 0; j < N; j++)         //for every point
        {
            //Compute distance centroid - point
            if (method == "@metric_space hamming")
            {
                dist = DistanceHamming(cluster[i]->getCentroid(), hamming[j]->getId());
            }                
            else if (method == "@metric euclidean")
            {                              
                distf = DistanceEuclidean(euclidean[j]->getId(),cluster[i]->getCentroid());
            }
            else if (method == "@metric cosine")
            {                
                distf = DistanceEuclidean(cosine[j]->getId(), cluster[i]->getCentroid() );
            }
            else
            {                
                if (j < N-2)
                {
                    int *row = distance->getRow(j);
                    dist = row[r];
                    cout << dist << endl;
                }
            }  

            if (method != "@metric euclidean" && method != "@metric cosine")
            {
                sum += dist;
                P[j] = sum *1.0;
            }
            else 
            {
                sumf += distf;
                P[j] = sumf *1.0 ;
            }
            

        }
        float x = (rand() / (RAND_MAX + 1.0))* P[j-1];
        for (int j = 0; j < N; j++)         //for every point
        {
            if (x < P[j])
            {
                r = j;
                break;
            }
        }
        
        /*Create cluster with coosen centroid r*/
        if (method == "@metric_space hamming")
            cluster[i+1] = new ClusterH(hamming[r]);
        else if (method == "@metric euclidean")
            cluster[i+1] = new ClusterE(euclidean[r]);
        else if (method == "@metric cosine")
            cluster[i+1] = new ClusterC(cosine[r]);
        else
            cluster[i+1] = new ClusterD(distance->getRow(r));  
    }  
}