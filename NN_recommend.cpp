#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "NN_recommend.h"


void NNRMDA(int k, int N, string method, vector <string> neighbours, int P, int items, Hamming *HammingPoint, CosineSim *CosinePoint,Euclidean *EuclideanPoint, ofstream &outputFile)
{

    if (method == "@metric_space hamming")
    {
        float sumsim;
        int i, p = 0, flag, rated_item; // rating = 0;
        string h, id = HammingPoint->getItem(), temp;
        float sim = 0, sum, sum_of_sim,rating = 0; ;
        //cout << id << endl;
        for (int i = 0; i < HammingPoint->getItem().length(); i++) //Count how many distances from other items the point has
        {
            h = id[i];
            if (h == "\t") {
                p++;
            }
        }
        //cout << p;
        double array[p + 1];
        
        for (int i=0; i< p+1; i++)
        {
            array[i] = 0 ; 
        }
        
        istringstream iss(id);
        for (auto& i : array) {
            iss >> i;
        }
       // for (i = 0; i < p+1; i++) cout << array[i] << endl;
        int full = 0;
        int top_recommendations[5], top_ratings[5];
        for( int z = 0; z < 5; z++) top_ratings[z] = 0;
        for( int z = 0; z < 5; z++) top_recommendations[z] = 0;
        for (int item = 1; item <= items; item++)     //For every item, find unrated and rate them with given method
        {
            flag = 0; sum = 0; sum_of_sim = 0;
            for (int j = 0; j < p+1; j++)
            {
                if (j % 2 == 0) if (array[j] == item){ flag = 1; break;}                
            }
            
            if (flag == 0)      //If item is unrated from this user
            {
                for ( int z = 0; z < P && z < neighbours.size(); z++)        //For every neighbor P
                {
                    /*Check if P neighbour has rated wanted item*/
                    id = neighbours[z]; p = 0;
                    for (int i = 0; i < HammingPoint->getItem().length(); i++) //Count how many distances from other items the point has
                    {
                        h = id[i];
                        if (h == "\t") {
                            p++;
                        }
                    }
                    /*Split item-ratings from others*/
                    int array[p+1];
                    istringstream iss(id);
                    for (auto& i : array) {
                        iss >> i;
                    }
                    
                    
                    /*Check if wanted item is rated from this user P*/
                    flag = 0; 
     
                   for (int j = 0; j < p+1; j++)
                    {
                        if (j % 2 == 0) rated_item = array[j];
                        if (rated_item == item) flag = 1;
                        if (flag == 1 && j % 2 != 0) 
                        rating = array[j]; 
                        flag = 2;
                        if (rating <= 2)
                        {
                            rating = 0;
                        }
                        else
                        {
                            rating = 1;
                        }
                        if (j == 1) temp = to_string(array[j]);
                        else temp = temp + to_string(array[j]);

                    }            
                     
                    float dist = DistanceHamming(HammingPoint->getId(), temp);
                    
                    if (flag == 0)  rating = 0;
                    sum = sum + (1/(1+dist) * rating); 
                    sum_of_sim = sum_of_sim + (1/(1+dist));                         //Σsim(u,v)     
                    sumsim = sum_of_sim;
                }
                rating =(1 / sumsim) * sum ;
                
                //cout << "We rated unrated item   " << rating << endl;
                
                if (full < 5)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if (top_ratings[j] == 0) //There are empty positions
                        {
                            top_ratings[j] = rating;
                            top_recommendations[j] = item;                           
                            break;
                        }                                            
                    }
                    full++; 
                }
                else
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (rating > top_ratings[i])
                        {
                            top_ratings[i] = rating;
                            top_recommendations[i] = item;
                            break;
                        }
                    }                        
                }
                
            }
        }
        //cout << "Recommendations for user" << endl;
        for (int i = 0; i < 5; i++) outputFile << "item" << top_recommendations[i] << "\t";
    }                
    else if (method == "@metric_space euclidean")
    {
        int i, p = 0, flag, rated_item, rating;
        string h, id = EuclideanPoint->getRatedItems(), temp;
        float sim = 0, sum, sum_of_sim;
        for (int i = 0; i <  EuclideanPoint->getRatedItems().length(); i++) //Count how many distances from other items the point has
        {
            h = id[i];
            if (h == "\t") {
                p++;
            }
        }
        double array[p + 1];
        istringstream iss(id);
        for (auto& i : array) {
            iss >> i;
        }
        //for (i = 0; i < p+1; i++) cout << array[i] << endl;
        int full = 0;
        int top_recommendations[5], top_ratings[5];
        for( int z = 0; z < 5; z++) top_ratings[z] = 0;
        for( int z = 0; z < 5; z++) top_recommendations[z] = 0;
        for (int item = 1; item <= items; item++)     //For every item, find unrated and rate them with given method
        {
            flag = 0; sum = 0; sum_of_sim = 0;
            for (int j = 0; j < p+1; j++)
            {
                if (j % 2 == 0) if (array[j] == item){ flag = 1; break;}                
            }
            
            if (flag == 0)      //If item is unrated from this user
            {
                for ( int z = 0; z < P && z < neighbours.size(); z++)        //For every neighbor P
                {
                    /*Check if P neighbour has rated wanted item*/
                    id = neighbours[z]; p = 0;
                    for (int i = 0; i < EuclideanPoint->getRatedItems().length(); i++) //Count how many distances from other items the point has
                    {
                        h = id[i];
                        if (h == "\t") {
                            p++;
                        }
                    }
                    /*Split item-ratings from others*/
                    double array[p + 1];
                    istringstream iss(id);
                    for (auto& i : array) {
                        iss >> i;
                    }

                    /*Check if wanted item is rated from this user P*/
                    flag = 0; 
                    double average = 0.0;

                    for (int j = 0; j < p+1; j++)
                    {
                        if (j % 2 != 0) average = average + array[j];
                        if (j % 2 == 0) rated_item = array[j];
                        if (rated_item == item) flag = 1;
                        if (flag == 1 && j % 2 != 0){ rating = array[j]; flag = 2;}   //R(u, i) for neighbor
                    }               

                    average = average / p+1 ;       //R(u) for neighbor!

                    for (int j = 0; j < p+1; j++)
                    {
                        if (j % 2 != 0) array[j] = array[j] - average;
                        if (j == 1) temp = to_string(array[j]);
                        else temp = temp + "\t" + to_string(array[j]);
                    }
                    float dist = DistanceEuclidean(EuclideanPoint->getId(), temp);
                    if (flag == 0)  rating = 0;
                    sum = sum + ((1.0/1.0+dist) * (rating - average));                //Σsim(u,v)*R(u, i) - R(u)
                    sum_of_sim = sum_of_sim + (1.0/1.0+dist);                         //Σsim(u,v)     
                }

                rating = EuclideanPoint->getRu()+ (1 / sum_of_sim) * sum;
                //cout << "We rated unrated item   " << rating << endl;
                
                if (full < 5)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if (top_ratings[j] == 0) //There are empty positions
                        {
                            top_ratings[j] = rating;
                            top_recommendations[j] = item;                           
                            break;
                        }                                            
                    }
                    full++; 
                }
                else
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (rating > top_ratings[i])
                        {
                            top_ratings[i] = rating;
                            top_recommendations[i] = item;
                            break;
                        }
                    }                        
                }
                
            }
        }
        //cout << "Recommendations for user" << endl;
        for (int i = 0; i < 5; i++) outputFile << "item" << top_recommendations[i] << "\t";
    }
    else 
    {
        int i, p = 0, flag, rated_item, rating;
        string h, id = CosinePoint->getRatedItems(), temp;
        float sim = 0, sum, sum_of_sim;
        for (int i = 0; i < CosinePoint->getRatedItems().length(); i++) //Count how many distances from other items the point has
        {
            h = id[i];
            if (h == "\t") {
                p++;
            }
        }
        double array[p + 1];
        istringstream iss(id);
        for (auto& i : array) {
            iss >> i;
        }
        //for (i = 0; i < p+1; i++) cout << array[i] << endl;
        int full = 0;
        int top_recommendations[5], top_ratings[5];
        for( int z = 0; z < 5; z++) top_ratings[z] = 0;
        for( int z = 0; z < 5; z++) top_recommendations[z] = 0;
        for (int item = 1; item <= items; item++)     //For every item, find unrated and rate them with given method
        {
            flag = 0; sum = 0; sum_of_sim = 0;
            for (int j = 0; j < p+1; j++)
            {
                if (j % 2 == 0) if (array[j] == item){ flag = 1; break;}                
            }
            
            if (flag == 0)      //If item is unrated from this user
            {
                for ( int z = 0; z < P && z < neighbours.size(); z++)        //For every neighbor P
                {
                    /*Check if P neighbour has rated wanted item*/
                    id = neighbours[z]; p = 0;
                    for (int i = 0; i < CosinePoint->getRatedItems().length(); i++) //Count how many distances from other items the point has
                    {
                        h = id[i];
                        if (h == "\t") {
                            p++;
                        }
                    }
                    /*Split item-ratings from others*/
                    double array[p + 1];
                    istringstream iss(id);
                    for (auto& i : array) {
                        iss >> i;
                    }
                    //for ( i = 0; i < p+1; i++) cout << array[i] << endl;
                    /*Check if wanted item is rated from this user P*/
                    flag = 0; 
                    double average = 0.0;

                    for (int j = 0; j < p+1; j++)
                    {
                        if (j % 2 != 0) average = average + array[j];
                        if (j % 2 == 0) rated_item = array[j];
                        if (rated_item == item) flag = 1;
                        if (flag == 1 && j % 2 != 0){ rating = array[j]; flag = 2;}   //R(u, i) for neighbor
                    }               

                    average = average / p+1 ;       //R(u) for neighbor!

                    for (int j = 0; j < p+1; j++)
                    {
                        if (j % 2 != 0) array[j] = array[j] - average;
                        if (j == 1) temp = to_string(array[j]);
                        else temp = temp + "\t" + to_string(array[j]);
                    }
                    int dist = DistanceCosine(CosinePoint->getId(), temp);
                    if (flag == 0)  rating = 0;
                    sum = sum + (dist * (rating - average));                //Σsim(u,v)*R(u, i) - R(u)
                    sum_of_sim = sum_of_sim + dist;                         //Σsim(u,v)     
                }
                rating = CosinePoint->getRu() + (1 / sum_of_sim) * sum;
                //cout << "We rated unrated item   " << rating << endl;
                
                if (full < 5)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if (top_ratings[j] == 0) //There are empty positions
                        {
                            top_ratings[j] = rating;
                            top_recommendations[j] = item;                           
                            break;
                        }                                            
                    }
                    full++; 
                }
                else
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (rating > top_ratings[i])
                        {
                            top_ratings[i] = rating;
                            top_recommendations[i] = item;
                            break;
                        }
                    }                        
                }
                
            }
        }
        //cout << "Recommendations for user" << endl;
        for (int i = 0; i < 5; i++) outputFile << "item" << top_recommendations[i] << "\t";
    }    
      
 
}

void NNRMDB(int k, int N, string method, Cluster **cluster, int items, Hamming **HammingPoint, CosineSim **CosinePoint,Euclidean **EuclideanPoint, ofstream &outputFile)
{
    ofstream outputfile("ResultsCluster.txt");
    if (method == "@metric_space hamming")
    {
        float sumsim;
        int i, p = 0, flag, rated_item; // rating = 0;
        string h, temp;
        float sim = 0, sum, sum_of_sim,rating = 0; ;
        for (int c = 0; c < k; c++)     //For every cluster 
        {
            //cout << "cluster   "  << c << endl;
            for (int u = 0; u < cluster[c]->GetSize(); u++) //For every user inside cluster
            {
                //cout << "user   "  << u<< endl;
                outputfile << "\nuser  " << u+1 << "\t";
                string id = cluster[c]->GetPointH(u)->getItem();
                for (int i = 0; i < cluster[c]->GetPointH(u)->getItem().length(); i++) //Count how many distances from other items the point has
                {
                    h = id[i];
                    if (h == "\t") {
                        p++;
                    }
                }
                double array[p + 1];

                for (int i=0; i< p+1; i++)
                {
                    array[i] = 0 ; 
                }

                istringstream iss(id);
                for (auto& i : array) {
                    iss >> i;
                }
               // for (i = 0; i < p+1; i++) cout << array[i] << endl;
                int full = 0;
                int top_recommendations[5], top_ratings[5];
                for( int z = 0; z < 5; z++) top_ratings[z] = 0;
                for( int z = 0; z < 5; z++) top_recommendations[z] = 0;
                for (int item = 1; item <= items; item++)     //For every item, find unrated and rate them with given method
                {
                    flag = 0; sum = 0; sum_of_sim = 0;
                    for (int j = 0; j < p+1; j++)
                    {
                        if (j % 2 == 0) if (array[j] == item){ flag = 1; break;}                
                    }

                    if (flag == 0)      //If item is unrated from this user
                    {
                        //cout << "unrated item   " << item << endl;
                        for ( int z = 0; z < cluster[c]->GetSize(); z++)        //For every neighbor P
                        {
                            /*Check if P neighbour has rated wanted item*/
                            id = cluster[c]->GetPointH(z)->getItem(); p = 0;
                            //cout << "P =    " << id << endl;
                            for (int i = 0; i < cluster[c]->GetPointH(u)->getItem().length(); i++) //Count how many distances from other items the point has
                            {
                                h = id[i];
                                if (h == "\t") {
                                    p++;
                                }
                            }
                            /*Split item-ratings from others*/
                            int array[p+1];
                            istringstream iss(id);
                            for (auto& i : array) {
                                iss >> i;
                            }

                            /*Check if wanted item is rated from this user P*/
                            flag = 0; 

                           for (int j = 0; j < p+1; j++)
                            {
                                if (j % 2 == 0) rated_item = array[j];
                                if (rated_item == item) flag = 1;
                                if (flag == 1 && j % 2 != 0) 
                                    rating = array[j]; 
                                    flag = 2;
                                    if (rating <= 2)
                                    {
                                        rating = 0;
                                    }
                                    else
                                    {
                                        rating = 1;
                                    }
                                    if (j == 1) temp = to_string(array[j]);
                                    else temp = temp + to_string(array[j]);

                            }            

                            float dist = DistanceHamming(cluster[c]->GetPointH(u)->getId(), temp);

                            if (flag == 0)  rating = 0;
                            sum = sum + (1/(1+dist) * rating); 
                            sum_of_sim = sum_of_sim + (1/(1+dist));                         //Σsim(u,v)     
                            sumsim = sum_of_sim;
                        }
                        rating =(1 / sumsim) * sum ;

                        //cout << "We rated unrated item   " << rating << endl;

                        if (full < 5)
                        {
                            for (int j = 0; j < 5; j++)
                            {
                                if (top_ratings[j] == 0) //There are empty positions
                                {
                                    top_ratings[j] = rating;
                                    top_recommendations[j] = item;                           
                                    break;
                                }                                            
                            }
                            full++; 
                        }
                        else
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                if (rating > top_ratings[i])
                                {
                                    top_ratings[i] = rating;
                                    top_recommendations[i] = item;
                                    break;
                                }
                            }                        
                        }

                    }
                }
                //cout << "Recommendations for user" << endl;
                for (int i = 0; i < 5; i++) outputfile << "item" << top_recommendations[i] << "\t";
                outputfile.flush();
            }
        }
    }                
    else if (method == "@metric euclidean")
    {
        int i, p = 0, flag, rated_item, rating;
        string h, temp;
        float sim = 0, sum, sum_of_sim;
        for (int c = 0; c < k; c++)     //For every cluster 
        {
            for (int u = 0; u < cluster[c]->GetSize(); u++) //For every user inside cluster
            {
                outputfile << "\nuser  " << u+1 << "\t";
                string id = cluster[c]->GetPointE(u)->getRatedItems();
                for (int i = 0; i < cluster[c]->GetPointE(u)->getRatedItems().length(); i++) //Count how many distances from other items the point has
                {
                    h = id[i];
                    if (h == "\t") {
                        p++;
                    }
                }
                double array[p + 1];
                istringstream iss(id);
                for (auto& i : array) {
                    iss >> i;
                }
                //for (i = 0; i < p+1; i++) cout << array[i] << endl;
                int full = 0;
                int top_recommendations[5], top_ratings[5];
                for( int z = 0; z < 5; z++) top_ratings[z] = 0;
                for( int z = 0; z < 5; z++) top_recommendations[z] = 0;
                for (int item = 1; item <= items; item++)     //For every item, find unrated and rate them with given method
                {
                    flag = 0; sum = 0; sum_of_sim = 0;
                    for (int j = 0; j < p+1; j++)
                    {
                        if (j % 2 == 0) if (array[j] == item){ flag = 1; break;}                
                    }

                    if (flag == 0)      //If item is unrated from this user
                    {
                        for ( int z = 0; z < cluster[c]->GetSize(); z++)        //For every neighbor P
                        {
                            /*Check if P neighbour has rated wanted item*/
                            id = cluster[c]->GetPointE(z)->getRatedItems(); p = 0;
                            for (int i = 0; i < cluster[c]->GetPointE(u)->getRatedItems().length(); i++) //Count how many distances from other items the point has
                            {
                                h = id[i];
                                if (h == "\t") {
                                    p++;
                                }
                            }
                            /*Split item-ratings from others*/
                            double array[p + 1];
                            istringstream iss(id);
                            for (auto& i : array) {
                                iss >> i;
                            }
                            //for ( i = 0; i < p+1; i++) cout << array[i] << endl;
                            /*Check if wanted item is rated from this user P*/
                            flag = 0; 
                            double average = 0.0;

                            for (int j = 0; j < p+1; j++)
                            {
                                if (j % 2 != 0) average = average + array[j];
                                if (j % 2 == 0) rated_item = array[j];
                                if (rated_item == item) flag = 1;
                                if (flag == 1 && j % 2 != 0){ rating = array[j]; flag = 2;}   //R(u, i) for neighbor
                            }               

                            average = average / p+1 ;       //R(u) for neighbor!

                            for (int j = 0; j < p+1; j++)
                            {
                                if (j % 2 != 0) array[j] = array[j] - average;
                                if (j == 1) temp = to_string(array[j]);
                                else temp = temp + "\t" + to_string(array[j]);
                            }
                            float dist = DistanceEuclidean(cluster[c]->GetPointE(u)->getId(), temp);
                            if (flag == 0)  rating = 0;
                            sum = sum + ((1.0/1.0+dist) * (rating - average));                //Σsim(u,v)*R(u, i) - R(u)
                            sum_of_sim = sum_of_sim + (1.0/1.0+dist);                             
                        }

                        rating = cluster[c]->GetPointE(u)->getRu() + (1 / sum_of_sim) * sum;
                        //cout << "We rated unrated item   " << rating << endl;

                        if (full < 5)
                        {
                            for (int j = 0; j < 5; j++)
                            {
                                if (top_ratings[j] == 0) //There are empty positions
                                {
                                    top_ratings[j] = rating;
                                    top_recommendations[j] = item;                           
                                    break;
                                }                                            
                            }
                            full++; 
                        }
                        else
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                if (rating > top_ratings[i])
                                {
                                    top_ratings[i] = rating;
                                    top_recommendations[i] = item;
                                    break;
                                }
                            }                        
                        }

                    }
                }
                //cout << "Recommendations for user" << endl;
                for (int i = 0; i < 5; i++) outputfile << "item" << top_recommendations[i] << "\t";
                outputfile.flush();
            }
        }
    }
    else 
    {
        int i, p = 0, flag, rated_item, rating;
        string h, temp;
        float sim = 0, sum, sum_of_sim;
        for (int c = 0; c < k; c++)     //For every cluster 
        {
            //cout << "cluster   " << c << endl;
            for (int u = 0; u < cluster[c]->GetSize(); u++) //For every user inside cluster
            {
                //cout << "user   " << u << endl;
                outputfile << "\nuser  " << u+1 << "\t";
                string id = cluster[c]->GetPointC(u)->getRatedItems();
                for (int i = 0; i < cluster[c]->GetPointC(u)->getRatedItems().length(); i++) //Count how many distances from other items the point has
                {
                    h = id[i];
                    if (h == "\t") {
                        p++;
                    }
                }
                double array[p + 1];
                istringstream iss(id);
                for (auto& i : array) {
                    iss >> i;
                }
                //for (i = 0; i < p+1; i++) cout << array[i] << endl;
                int full = 0;
                int top_recommendations[5], top_ratings[5];
                for( int z = 0; z < 5; z++) top_ratings[z] = 0;
                for( int z = 0; z < 5; z++) top_recommendations[z] = 0;
                for (int item = 1; item <= items; item++)     //For every item, find unrated and rate them with given method
                {
                    flag = 0; sum = 0; sum_of_sim = 0;
                    for (int j = 0; j < p+1; j++)
                    {
                        if (j % 2 == 0) if (array[j] == item){ flag = 1; break;}                
                    }

                    if (flag == 0)      //If item is unrated from this user
                    {
                        for ( int z = 0; z < cluster[c]->GetSize(); z++)        //For every neighbor P
                        {
                            /*Check if P neighbour has rated wanted item*/
                            id = cluster[c]->GetPointC(z)->getRatedItems(); p = 0;
                            for (int i = 0; i < cluster[c]->GetPointC(u)->getRatedItems().length(); i++) //Count how many distances from other items the point has
                            {
                                h = id[i];
                                if (h == "\t") {
                                    p++;
                                }
                            }
                            /*Split item-ratings from others*/
                            double array[p + 1];
                            istringstream iss(id);
                            for (auto& i : array) {
                                iss >> i;
                            }
                            //for ( i = 0; i < p+1; i++) cout << array[i] << endl;
                            /*Check if wanted item is rated from this user P*/
                            flag = 0; 
                            double average = 0.0;

                            for (int j = 0; j < p+1; j++)
                            {
                                if (j % 2 != 0) average = average + array[j];
                                if (j % 2 == 0) rated_item = array[j];
                                if (rated_item == item) flag = 1;
                                if (flag == 1 && j % 2 != 0){ rating = array[j]; flag = 2;}   //R(u, i) for neighbor
                            }               

                            average = average / p+1 ;       //R(u) for neighbor!

                            for (int j = 0; j < p+1; j++)
                            {
                                if (j % 2 != 0) array[j] = array[j] - average;
                                if (j == 1) temp = to_string(array[j]);
                                else temp = temp + "\t" + to_string(array[j]);
                            }
                            int dist = DistanceCosine(cluster[c]->GetPointC(u)->getId(), temp);
                            if (flag == 0)  rating = 0;
                            sum = sum + (dist * (rating - average));                //Σsim(u,v)*R(u, i) - R(u)
                            sum_of_sim = sum_of_sim + dist;                         //Σsim(u,v)     
                        }
                        rating = cluster[c]->GetPointC(u)->getRu() + (1 / sum_of_sim) * sum;
                        //cout << "We rated unrated item   " << rating << endl;

                        if (full < 5)
                        {
                            for (int j = 0; j < 5; j++)
                            {
                                if (top_ratings[j] == 0) //There are empty positions
                                {
                                    top_ratings[j] = rating;
                                    top_recommendations[j] = item;                           
                                    break;
                                }                                            
                            }
                            full++; 
                        }
                        else
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                if (rating > top_ratings[i])
                                {
                                    top_ratings[i] = rating;
                                    top_recommendations[i] = item;
                                    break;
                                }
                            }                        
                        }

                    }
                }
                //cout << "Recommendations for user" << endl;
                for (int i = 0; i < 5; i++) outputfile << "item" << top_recommendations[i] << "\t";
                outputfile.flush();
            }
        }
        
    }    
      
 
}


