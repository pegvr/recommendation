#include "PAM.h"
#include "Cluster.h"


 
void PAM(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int *objectivefunction, float * ObjectiveFunctionF)
{
    int i, j, dist, min_dist, min_k;
    float distf, min_distf;
    for (i = 0; i < N; i++)             //For every point
    {
        min_dist = 100000;
        min_distf = 10000;
        for (j = 0; j < k; j++)         //For every cluster compute nearest centroid from point
        {
            if (method == "@metric_space hamming")
            {
                dist = DistanceHamming(cluster[j]->getCentroid(), hamming[i]->getId());
                                             
            }                
            else if (method == "@metric euclidean")
            {
                distf = DistanceEuclidean(euclidean[i]->getId(), cluster[j]->getCentroid());
            }
            else if (method == "@metric cosine")
            {

                distf = DistanceEuclidean(cosine[i]->getId(), cluster[j]->getCentroid());
            }
            else
            {   
                int *row = distance->getRow(j);
                dist = row[j];
            }  
            if ((dist < min_dist && dist != 0) || (distf < min_distf && distf != 0))    
            {
                min_dist = dist;
                min_distf = distf;
                min_k = j;
            }  
        }

        objectivefunction[min_k] += dist;
        ObjectiveFunctionF[min_k] += distf;
        
        if (method == "@metric_space hamming")
        {
            cluster[min_k]->InsertPointH(hamming[i], min_dist); //Insert point into nearest cluster
            min_dist = 10000;
            int sc;
            for (int p = 0; p < k; p++)     //Find second best cluster
            {
                if (p != min_k)
                {

                    dist = DistanceHamming(cluster[p]->getCentroid(), hamming[i]->getId());
                    if (dist < min_dist && dist != 0)
                    {
                        min_dist = dist;
                        sc = p;
                    }  
                }
            }
            cluster[min_k]->SecondCentroid(sc, min_dist);
        }            
        else if (method == "@metric euclidean") 
        {
            cluster[min_k]->InsertPointE(euclidean[i], min_distf);   //Insert point into nearest cluster
            min_distf = 10000;
            int sc;
            for (int p = 0; p < k; p++)    //Find second best cluster
            {
                if (p != min_k)
                {
                    distf = DistanceEuclidean(euclidean[i]->getId(), cluster[p]->getCentroid());
                    if (distf < min_distf && distf != 0)
                    {
                        min_distf = distf;
                        sc = p;
                    }  
                }
            }
            cluster[min_k]->SecondCentroid(sc, min_distf);
        }
        else if (method == "@metric cosine")
        {
            cluster[min_k]->InsertPointC(cosine[i], min_distf);  //Insert point into nearest cluster
            min_distf = 10000.0;
            int sc;
            for (int p = 0; p < k; p++)    //Find second best cluster
            {
                if (p != min_k)
                {
                    distf = DistanceEuclidean(cosine[i]->getId(), cluster[p]->getCentroid());
                    if (distf < min_distf && distf != 0)
                    {
                        min_distf = distf;
                        sc = p;
                    }  
                }
            }
            cluster[min_k]->SecondCentroid(sc, min_distf);
        }
        else
        {
           cluster[min_k]->InsertPointD(distance->getRow(i), min_dist);
           if(j != min_k){
                int *row = distance->getRow(j);
                dist = row[j];
           }
           cluster[min_k]->SecondCentroid(j, dist);
        }

    }

}


void PAM_Update(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int *objectivefunction, float * ObjectiveFunctionF)
{
    int i, j, dist, min_dist, min_k, flag, position;
    float distf, min_distf;
    for (i = 0; i < N; i++)   //For every point
    {
        min_dist = 100000;
        min_distf = 100000.0;
        for (j = 0; j < k; j++)         //For every cluster
        {
            if (method == "@metric_space hamming")  //Compute distance point-cluster
            {
                dist = DistanceHamming(cluster[j]->getCentroid(), hamming[i]->getId());
                for (int t = 0; t < cluster[j]->GetSize(); t++)     //Check where point already belongs
                {
                    if (hamming[i]->getId() == cluster[j]->GetPointH(t)->getId())
                    {
                        flag = j;               //Cluster where point belongs
                        position = t;           //Position in cluster where point belongs
                        break;
                    }                
                }                                            
            }                
            else if (method == "@metric euclidean")
            {
                distf = DistanceEuclidean(euclidean[i]->getId(), cluster[j]->getCentroid());
                for (int t = 0; t < cluster[j]->GetSize(); t++)  //Check where point already belongs
                {
                    if (euclidean[i]->getId() == cluster[j]->GetPointE(t)->getId())
                    {
                        flag = j;           //Cluster where point belongs
                        position = t;           //Position in cluster where point belongs
                        break;
                    }                
                }
            }
            else if (method == "@metric cosine")
            {
                distf = DistanceEuclidean(cosine[i]->getId(), cluster[j]->getCentroid()); 
                for (int t = 0; t < cluster[j]->GetSize(); t++)   //Check where point already belongs
                {
                    if (cosine[i]->getId() == cluster[j]->GetPointC(t)->getId())
                    {
                        flag = j;                //Cluster where point belongs
                        position = t;           //Position in cluster where point belongs
                        break;
                    }                
                }
            }
            else
            {   
                int *row = distance->getRow(i);
                dist = row[j];
            }  
            if ((dist < min_dist && dist != 0) || (distf < min_distf && distf != 0))       
            {
                min_dist = dist;
                min_distf = distf;
                min_k = j;
            }  
            
        }
        objectivefunction[min_k] += dist;
        ObjectiveFunctionF[min_k] += distf;
        if (min_k != flag)                         //If point needs to be assigned again to another cluster
        { 
            cluster[flag]->PopPoint(position);     //Pop point from cluster
            cluster[flag]->PopSecondCentroid(position);
            /*Insert now point into the right cluster, after the update of the centroid*/
            if (method == "@metric_space hamming")  
            {
                cluster[min_k]->InsertPointH(hamming[i], min_dist);
                min_dist = 10000;
                int sc;
                for (int p = 0; p < k; p++)
                {
                    if (p != min_k)
                    {

                        dist = DistanceHamming(cluster[p]->getCentroid(), hamming[i]->getId());
                        if (dist < min_dist && dist != 0)
                        {
                            min_dist = dist;
                            sc = p;
                        }  
                    }
                }
                cluster[min_k]->SecondCentroid(sc, min_dist);
            }            
            else if (method == "@metric euclidean")
            {
                cluster[min_k]->InsertPointE(euclidean[i], min_distf);
                min_distf = 10000.0;
                int sc;
                for (int p = 0; p < k; p++)
                {
                    if (p != min_k)
                    {
                        distf = DistanceEuclidean(euclidean[i]->getId(), cluster[p]->getCentroid());
                        if (distf < min_distf && distf != 0)
                        {
                            min_distf = distf;
                            sc = p;
                        }  
                    }
                }
                cluster[min_k]->SecondCentroid(sc, min_distf);
            }
            else if (method == "@metric cosine")
            {
                cluster[min_k]->InsertPointC(cosine[i], min_distf);
                min_distf = 10000.0;
                int sc;
                for (int p = 0; p < k; p++)
                {
                    if (p != min_k)
                    {
                        distf = DistanceEuclidean(cosine[i]->getId(), cluster[p]->getCentroid());
                        if (distf < min_distf && distf != 0)
                        {
                            min_distf = distf;
                            sc = p;
                        }  
                    }
                }
                cluster[min_k]->SecondCentroid(sc, min_distf);
            }
            else
            {
               cluster[min_k]->InsertPointD(distance->getRow(i), min_dist);
               if(j != min_k){
                    int *row = distance->getRow(j);
                    dist = row[j];
               }
               cluster[min_k]->SecondCentroid(j, dist);
            }
        }
    }
}
