#include "Silhouette.h"


void Silhouette(Cluster **cluster, int k, int N, string method, float *s)
{
    int i, j, t, dist;
    float distf, a[N], b[N];
    for(i = 0; i < N; i++) a[i] = 0;
    for(i = 0; i < N; i++) b[i] = 0;
    for(i = 0; i < k; i++) s[i] = 0;
    for(i = 0; i < k; i++)              //For every cluster
    {
        
        for (j = 0; j < cluster[i]->GetSize(); j++)  //For each point compute distance from other points in cluster
        {
            for (t = 0; t < cluster[i]->GetSize(); t++)  
            {
                if (method == "@metric_space hamming")
                {
                    distf = DistanceHamming(cluster[i]->GetPointH(t)->getId(), cluster[i]->GetPointH(j)->getId());

                }                
                else if (method == "@metric euclidean")
                {
                    distf = DistanceEuclidean(cluster[i]->GetPointE(t)->getId(), cluster[i]->GetPointE(j)->getId());

                }
                else if (method == "@metric cosine")
                {

                    distf = DistanceEuclidean(cluster[i]->GetPointC(t)->getId(), cluster[i]->GetPointC(j)->getId());
                }
                else
                {   
                    int *row = cluster[i]->GetPointD(j);
                    distf = row[t];
                }  
                a[j] += distf;
            }    
            if (cluster[i]->GetSize() != 0)
                a[j] = a[j]*1.0 / cluster[i]->GetSize();
            
            int secondbestcluster = cluster[i]->GetSecondCentroid(j);
            for (t = 0; t < cluster[secondbestcluster]->GetSize(); t++)  //For each point compute distance from other points in second best cluster
            {
                if (method == "@metric_space hamming")
                {
                    distf = DistanceHamming(cluster[secondbestcluster]->GetPointH(t)->getId(), cluster[i]->GetPointH(j)->getId());

                }                
                else if (method == "@metric euclidean")
                {
                    distf = DistanceEuclidean(cluster[secondbestcluster]->GetPointE(t)->getId(), cluster[i]->GetPointE(j)->getId());
                }
                else if (method == "@metric cosine")
                {

                    distf = DistanceEuclidean(cluster[secondbestcluster]->GetPointC(t)->getId(), cluster[i]->GetPointC(j)->getId());
                }
                else
                {   
                    int *row = cluster[secondbestcluster]->GetPointD(j);
                    distf = row[t];
                }  
                b[t] += distf;
            }    
            if (cluster[secondbestcluster]->GetSize() != 0)
                b[j] = b[j]*1.0 / cluster[secondbestcluster]->GetSize();
            
            int temp = (b[j] < a[j]) ? a[j] : b[j] ;
            s[i] += (b[j] - a[j]) *1.0/ temp;
            //cout << "silhouette of   " << j << "     " << s << endl;
        }
        if (cluster[i]->GetSize() != 0)
            s[i] = s[i] *1.0 / cluster[i]->GetSize();
    }
    
}
