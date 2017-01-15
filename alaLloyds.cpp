#include "alaLloyds.h"

void alalloyds(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int *objectivefunction, float * ObjectiveFunctionF)
{
    int i, j, t, z, dist,  OF,min_OF , medoid;
    float OFF, min_OFF,distf;
    
    for ( i = 0; i < k; i++)        //For every cluster
    {
        min_OF = objectivefunction[i];
        min_OFF = ObjectiveFunctionF[i];
        for (t = 0; t < cluster[i]->GetSize(); t++)         //Find if t is a medoid
        {
            int newdistances[cluster[i]->GetSize()];
            float newdistancesf[cluster[i]->GetSize()];
            OF = 0;
            OFF = 0;
            for (j = 0; j < cluster[i]->GetSize(); j++)     //Compute distance from possible medoid t to j points in same cluster
            {
                if (method == "@metric_space hamming")
                {
                    dist = DistanceHamming(cluster[i]->GetPointH(j)->getId(), cluster[i]->GetPointH(t)->getId());
                    newdistances[j] = dist;    
                }                
                else if (method == "@metric euclidean")
                {
                    distf = DistanceEuclidean(cluster[i]->GetPointE(j)->getId(), cluster[i]->GetPointE(t)->getId());
                    newdistancesf[j] = distf;  
                }
                else if (method == "@metric cosine")
                {                    
                    distf = DistanceEuclidean(cluster[i]->GetPointC(t)->getId(), cluster[i]->GetPointC(j)->getId());
                    newdistancesf[j] = distf;
                }
                else
                {   
                    int *row = distance->getRow(j);
                    dist = row[j];
                    newdistances[j] = dist;
                }  

                OF += dist;
                OFF += distf;
            
            }
            if (OF < min_OF || OFF < min_OFF) //If objective function of point is better then we have a possible medoid
            {
                min_OF = OF;
                min_OFF = OFF;
                medoid = t;   
            }
     
        }
        /*If objective fynction of medoid is better than the one we already have, update centroid*/
        if (min_OF < objectivefunction[i] || min_OFF < ObjectiveFunctionF[i])
        {
            if (method == "@metric_space hamming")
                cluster[i]->UpdateCentroid(cluster[i]->GetPointH(medoid)->getId());
            else if (method == "@metric euclidean")
                cluster[i]->UpdateCentroid(cluster[i]->GetPointE(medoid)->getId());
            else if (method == "@metric cosine")
                cluster[i]->UpdateCentroid(cluster[i]->GetPointC(medoid)->getId());
            else
                cluster[i]->UpdateCentroid(distance->getName());
            objectivefunction[i] = min_OF;
            ObjectiveFunctionF[i] = min_OFF;
            PAM_Update(cluster, k, N, method, hamming, cosine, euclidean, distance, objectivefunction, ObjectiveFunctionF);
        }   
    }
}
