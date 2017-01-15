#include "Park_Jun.h"

void ParkJun(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance)
{
    int i, j, t, dist, sumt;
    int sum[N];
    int matrix[N][N];
    float distf, matrixf[N][N], sumf[N], sumtf;

    for(i = 0; i < N; i++) sum[i] = 0;

    for(i = 0; i < N; i++) sumf[i] = 0;

    /*For method compute 2-dimension matrix*/
    if (method == "@metric_space hamming")
    {
        for ( i = 0 ; i < N; i++)
        {
            for(j = 0 ; j < N; j++)
            {
                dist = DistanceHamming(hamming[j]->getId(),hamming[i]->getId() );
                matrix[i][j] = dist;
            }
        }
        for (i = 0 ; i < N; i++)
        {
            for (j = 0 ; j < N; j++)
            {
                sumt = 0 ;
                for (t = 0 ; t < N; t++)    sumt += matrix[j][t];
                
                sum[i] += matrix [i][j] / sumt;
            
            }
        }

        for (i = 0 ; i < k; i++)    //For every cluster find centroid
        {
            int minsum = 100000, min_object;
            for (j = 0 ; j < N; j++)
            {
                if (sum[i] < minsum){ minsum = sum[j]; min_object = i;}
            }
            cluster[i] = new ClusterH(hamming[min_object]);
        }
    }           
    else if (method == "@metric euclidean")
    {
        for ( i = 0 ; i < N; i++)
        {
            for(j = 0 ; j < N; j++)
            {               
                distf = DistanceEuclidean(euclidean[j]->getId(),euclidean[i]->getId() );
                matrixf[i][j] = distf;
            }
        }
        for (i = 0 ; i < N; i++)
        {
            for (j = 0 ; j < N; j++)
            {
                sumtf = 0 ;
                for (t = 0 ; t < N; t++)    sumtf += matrixf[j][t];
                
                sumf[i] += matrixf [i][j] / sumtf;
            
            }
        }

        for (i = 0 ; i < k; i++)  //For every cluster find centroid
        {
            float minsumf = 100000.0;
            int min_object;
            for (j = 0 ; j < N; j++)
            {
                if (sumf[i] < minsumf){ minsumf = sumf[j]; min_object = i;}
            }
            cluster[i] = new ClusterE(euclidean[min_object]);
        }
    }
    else if (method == "@metric cosine")
    {
        cout << "1" << endl;
        for ( i = 0 ; i < N; i++)
        {
            cout << "2" << endl;
            for(j = 0 ; j < N; j++)
            {
                cout << "3" << endl;
                distf = DistanceEuclidean(cosine[j]->getId(),cosine[i]->getId() );
                matrixf[i][j] = dist;
            }
        }
        cout << "4" << endl;
        for (i = 0 ; i < N; i++)
        {
            cout << "5" << endl;
            for (j = 0 ; j < N; j++)
            {
                cout << "6" << endl;
                sumtf = 0 ;
                for (t = 0 ; t < N; t++)    sumtf += matrixf[j][t];
                
                sumf[i] += matrixf [i][j] / sumtf;
            
            }
        }
        cout << "7" << endl;
        for (i = 0 ; i < k; i++)  //For every cluster find centroid
        {
            cout << "8" << endl;
            float minsum = 100000.0;
            int min_object;
            for (j = 0 ; j < N; j++)
            {
                cout << "9" << endl;
                if (sumf[i] < minsum){ minsum = sumf[j]; min_object = i;}
            }
            cluster[i] = new ClusterC(cosine[min_object]);
            cout << "10" << endl;
        }
    }
    else
    {
        for (i = 0 ; i < N-2; i++)
        {
            for (j = 0 ; j < N-2; j++)
            {
                sumt = 0 ;
                int * dist = distance->getRow(j);

                
                for (t = 0 ; t < N-2; t++)   
                {  
                    sumt += dist[t];
                    cout << dist[t]<< endl;  
                }
                dist = distance->getRow(i);
                sum[i] += dist[j] / sumt;
            }
        }

        for (i = 0 ; i < k; i++)
        {
            int minsum = 100000, min_object;
            for (j = 0 ; j < N-2; j++)
            {
                if (sum[i] < minsum){ minsum = sum[j]; min_object = i;}
            }
            cluster[i] = new ClusterD(distance->getRow(min_object));
        }
    } 
    
}
