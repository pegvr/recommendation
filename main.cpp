#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include "../Eigen/Dense"
#include "LSH.h"
#include "Cluster.h"
#include "randomfunc.h"
#include "Silhouette.h"
#include "NN_recommend.h"
#include "CosineSim.h"
#include "Hashtable.h"
#include "K_medoids.h"
#include "PAM.h"
#include "alaLloyds.h"
#include "Park_Jun.h"

using namespace std;
using namespace Eigen;

/*
 * 
 */
string Rate(string rate,string method, double &average);
void QuerySearch(char *tmp1, char *tmp2, char *tmp, Hashtable **PointersToHashtable, int L, int k, string method, int N, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, int P);

int main(int argc, char** argv) 
{
    int  choice, k, L, NumofHashFUnctions, N, i;
    string line, temp, method, option ;
    bool gameOn = true ;
    size_t pos;
    k = 10;
    L = 5;  
    
    ifstream inputfile(argv[2]);
    if (inputfile.is_open())
    {
        getline (inputfile,line);
        pos = line.find("\t");
        string temp1 = line.substr(0, pos);//Name of point: itemY
        //cout << line << "       " << temp1 << endl;
        if (temp1 == "P:")
            temp = line.substr(pos, line.size()-2);
        else 
            temp = "20";

        int counter = 0;
        while ( getline (inputfile,line) ) counter++; 
        //cout << "counter:" << counter << endl;
        int n = counter - 1 ; 
        inputfile.clear();
        inputfile.seekg(0, ios::beg);
        for (int i = 0; i < n; i++) getline (inputfile,line);


        pos = line.find("\t");
        temp1 = line.substr(0, pos);//Name of point: itemY
        N = stoi(temp1, nullptr, 10);
        //cout << "N = " << N << endl;

        int num = 0; 

        int P;
        P = stoi(temp, nullptr, 10);
        
        
        while (gameOn != false)
        {
            cout << "*******************************\n";
            cout << " Α.Method: Choose ΝΝ-LSH Recommendation\n";
            cout << " B.Method: Choose Clustering Recommendation\n";
            cout << "Press A for ΝΝ-LSH Recommendation or B for Clustering Recommendation\n";
            cin >> option;
            cout << " 1 - Recommendation with Cosine Similarity \n";
            cout << " 2 - Recommendation with Hamming \n";
            cout << " 3 - Recommendation with Euclidean \n\n";
            cout << " Enter your choice and press return: ";

            cin >> choice;
        
            cout << "*******************************\n\n";
        
        
            switch (choice)
            {
                case 1:
                {
                    string g, rate, tmp_rate, R, item, tmp_item;
                    int i, flag = 0;
                    int j = 0;
                    streampos oldpos;
                    Hashtable **PointersToHashtable = CreateHash(L, k, 0);      //Construct L HashTables
                    CosineSim **cosine = new CosineSim*[N];               //Construct as many pointers to Cosine Classes as the num of points in given file
                    inputfile.clear();
                    inputfile.seekg(0, ios::beg);
                    while ( getline (inputfile,line))
                    {
                        pos = line.find("\t");
                        string temp1 = line.substr(0, pos); //userid
                        temp = line.substr(pos+1, line.size());
                        pos = temp.find("\t");
                        if (flag == 1) {item = tmp_item + "\t" + temp;}
                        else item = temp; //item                        
                        temp = temp.substr(pos+1, temp.size()); //ratings
                        if (flag == 1) {rate = tmp_rate + "\t" + temp ; flag =0;}
                        else rate = temp; 
                        while(getline(inputfile,line))
                        {
                            pos = line.find("\t");
                            string temp2 = line.substr(0, pos); //userid
                            if(temp2 == temp1)
                            {
                                temp = line.substr(pos+1, line.size());
                                pos = temp.find("\t");
                                item = item + "\t" + temp; //item
                                temp = temp.substr(pos+1, temp.size());
                                rate = rate + "\t" + temp;
                            }
                            else
                            {   
                                pos = line.find("\t");
                                string temp2 = line.substr(0, pos); //userid
                                temp = line.substr(pos+1, line.size());
                                pos = temp.find("\t");
                                tmp_item = temp; //item
                                temp = temp.substr(pos+1, temp.size());
                                tmp_rate = temp;
                                flag = 1;
                                break;
                            }

                        } 

                        double Ru;
                        R = Rate(rate,"cosine", Ru);
                        cosine[j] = new CosineSim(R, temp1, item, Ru);  //Construct cosine class for point j  

                        if(option == "A")
                        {
                            for (i = 0; i < L; i++)             //insert point into all hashtables
                            { 
                                g = cosine[j]->ConstructGFunctionC(k);      //g function = concatenation of random h               
                                PointersToHashtable[i]->InsertIntoHashtable(g, NULL, cosine[j], NULL, NULL, -1);    //Insert Cosine point into HashtableI
                            }
                        }                         
                        j++;
                    } 
                    inputfile.close();

                    string method = "@metric_space cosine";
                    if(option == "A") QuerySearch(argv[2], argv[10], argv[4], PointersToHashtable, L, k, method, N, NULL, cosine, NULL, P);    //Search NN
                    if(option == "B") 
                    {
                        method = "@metric cosine";
                        ofstream outputFile("Results.txt");
                        Cluster **cluster = new Cluster*[k];
                        int ObjectiveFunction[k];
                        float ObjectiveFunctionF[k];
                        
                        k_medoidspp( cluster, k, N, method, NULL, cosine, NULL, NULL);                        
                        //for (i = 0; i < k; i++) cout << cluster[i]->getCentroid() << endl;                        
                        for (i = 0; i < k; i++) ObjectiveFunction[i] = 0;
                        for (i = 0; i < k; i++) ObjectiveFunctionF[i] = 0;

                        PAM(cluster, k, N, method, NULL, cosine, NULL, NULL, ObjectiveFunction, ObjectiveFunctionF);
                        //for (i = 0; i < k; i++) cout << ObjectiveFunction[i] << endl;
                        //for (i = 0; i < k; i++) cout << cluster[i]->GetSize() << endl;

                        //alalloyds(cluster, k, N, method, NULL, cosine, NULL, NULL, ObjectiveFunction, ObjectiveFunctionF);
                        cout << "after allalalala " << endl;
                        float s[k], sum = 0;
                        Silhouette(cluster,  k,  N,  method, s);
                        outputFile << "Silhouette: [ " ;
                        for (i = 0; i < k; i++)
                        {
                            sum += s[i];
                            outputFile << s[i] << " , ";
                            outputFile.flush();
                        }       
                        outputFile <<  " ] "<< endl;
                        outputFile <<  " Sum: "<< sum << endl;
                        outputFile.flush();

                        outputFile << "\n\n\nNNRMDB  " << j+1 << "\t";
                        NNRMDB( k,  N,  method, cluster, 1000, NULL, cosine, NULL, outputFile);
                        for (i = 0; i < k; i++) delete cluster[i];
                    }
                    for (i = 0; i < L; i++) delete PointersToHashtable[i];
                    for (i = 0; i < j; i++) delete cosine[i];
                }
                break;
                case 2:
                {
                    string g, rate, tmp_rate, R, item, tmp_item;
                    int i, flag = 0;
                    int j = 0;
                    streampos oldpos;
                    Hashtable **PointersToHashtable = CreateHash(L, k, 0);      //Construct L HashTables
                    Hamming **hamming = new Hamming*[N];              //Construct as many pointers to Cosine Classes as the num of points in given file
                    inputfile.clear();
                    inputfile.seekg(0, ios::beg);
                    while ( getline (inputfile,line))
                    {
                        //cout << "new    " << line << endl;
                        pos = line.find("\t");
                        string temp1 = line.substr(0, pos); //userid
                        temp = line.substr(pos+1, line.size());
                        pos = temp.find("\t");
                        if (flag == 1) {item = tmp_item + "\t" + temp;}
                        else item = temp; //item 
                        temp = temp.substr(pos+1, temp.size()); //ratings
                        if (flag == 1) {rate = tmp_rate + "\t" + temp ; flag =0;}
                        else rate = temp; 

                        while(getline(inputfile,line))
                        {
                            pos = line.find("\t");
                            string temp2 = line.substr(0, pos); //userid
 
                            if(temp2 == temp1)
                            {
                                temp = line.substr(pos+1, line.size());
                                pos = temp.find("\t");
                                item = item + "\t" + temp; //item
                                temp = temp.substr(pos+1, temp.size());
                                rate = rate + "\t" + temp; 
                            }
                            else
                            {   
                                pos = line.find("\t");
                                string temp2 = line.substr(0, pos); //userid
                                temp = line.substr(pos+1, line.size());
                                pos = temp.find("\t");
                                tmp_item = temp; //item
                                temp = temp.substr(pos+1, temp.size());
                                tmp_rate = temp;
                                flag = 1;
                                break;
                            }
                            
                        } 
 
                        double Ru;
                        R = Rate(rate,"hamming", Ru);

                        hamming[j] = new Hamming(R,temp1,item,Ru);     //Construct hamming class for point j

                       if(option == "A") 
                        {
                            for (i = 0; i < L; i++)             //insert point into all hashtables
                            { 
                                g = hamming[j]->ConstructGFunction(k);    //g function = concatenation of random h
                                // cout << g;
                                PointersToHashtable[i]->InsertIntoHashtable(g, hamming[j], NULL, NULL, NULL, -1); //Insert Hamming point into HasttableI

                            }
                        }
                        j++;
                    } 
                    inputfile.close();
                    string method = "@metric_space hamming";
                    if(option == "A") QuerySearch(argv[2], argv[10], argv[4],PointersToHashtable, L, k, method, N, hamming, NULL, NULL, P); //Search NN
                    if(option == "B") 
                    {                        
                        Cluster **cluster = new Cluster*[k];
                        ofstream outputFile("Results.txt");
                        int ObjectiveFunction[k];
                        float ObjectiveFunctionF[k];

                        k_medoidspp( cluster, k, N, method, hamming, NULL, NULL, NULL);
                        for (i = 0; i < k; i++) cout << cluster[i]->getCentroid() << endl;   
                        
                        for (i = 0; i < k; i++) ObjectiveFunction[i] = 0;
                        for (i = 0; i < k; i++) ObjectiveFunctionF[i] = 0;

                        PAM(cluster, k, N, method, hamming, NULL, NULL, NULL, ObjectiveFunction, ObjectiveFunctionF);
                        for (i = 0; i < k; i++) cout << ObjectiveFunction[i] << endl;
                        for (i = 0; i < k; i++) cout << cluster[i]->GetSize() << endl;   
                        alalloyds(cluster, k, N, method, hamming, NULL, NULL, NULL, ObjectiveFunction, ObjectiveFunctionF);
                        cout << "after allalalala " << endl;
                        
                        float s[k], sum = 0;
                        Silhouette(cluster,  k,  N,  method, s);
                        outputFile << "Silhouette: [ " ;
                        for (i = 0; i < k; i++)
                        {
                            sum += s[i];
                            outputFile << s[i] << " , ";
                            outputFile.flush();
                        }       
                        outputFile <<  " ] "<< endl;
                        outputFile <<  " Sum: "<< sum << endl;
                        outputFile.flush();
                        NNRMDB( k,  N,  method, cluster, 1000, hamming, NULL, NULL, outputFile);
                        for (i = 0; i < k; i++) delete cluster[i];
                    }
                    for (i = 0; i < L; i++) delete PointersToHashtable[i];
                    for (i = 0; i < j; i++) delete hamming[i];
                }
                break;
                case 3:    
                {
                    string g, rate, tmp_rate, R, item, tmp_item;
                   int i, flag = 0;
                   int j = 0;
                   streampos oldpos;
                   Hashtable **PointersToHashtable = CreateHash(L, k, N);      //Construct L HashTables
                   Euclidean **euclidean = new Euclidean*[N];               //Construct as many pointers to Cosine Classes as the num of points in given file
                   inputfile.clear();
                   inputfile.seekg(0, ios::beg);
                   while ( getline (inputfile,line))
                   {
                        //cout << "new    " << line << endl;
                        pos = line.find("\t");
                        string temp1 = line.substr(0, pos); //userid
                        temp = line.substr(pos+1, line.size());
                        pos = temp.find("\t");
                        if (flag == 1) {item = tmp_item + "\t" + temp;}
                        else item = temp; //item 
                        temp = temp.substr(pos+1, temp.size()); //ratings
                        if (flag == 1) {rate = tmp_rate + "\t" + temp ; flag =0;}
                        else rate = temp; 
                        counter = 0;
                        while(getline(inputfile,line))
                        {
                            pos = line.find("\t");
                            string temp2 = line.substr(0, pos); //userid
                            if(temp2 == temp1)
                            {
                                //counter++;
                                temp = line.substr(pos+1, line.size());
                                pos = temp.find("\t");
                                item = item + "\t" + temp; //item
                                temp = temp.substr(pos+1, temp.size());
                                rate = rate + "\t" + temp;
                            }
                            else
                            {   
                                pos = line.find("\t");
                                string temp2 = line.substr(0, pos); //userid
                                temp = line.substr(pos+1, line.size());
                                pos = temp.find("\t");
                                tmp_item = temp; //item
                                temp = temp.substr(pos+1, temp.size());
                                tmp_rate = temp;
                                flag = 1;
                                break;
                            }
                            
                        } 
                        double Ru;
                        R = Rate(rate,"euclidean", Ru);  
                        euclidean[j] = new Euclidean(R, temp1,item,Ru);  //Construct euclidean class for point j  
 
                        if(option == "A")
                        {
                            for (i = 0; i < L; i++)             //insert point into all hashtables
                            { 
                               int length = PointersToHashtable[i]->getLength();
                               int fi = euclidean[j]->ConstructFiFunctionC(length, k); 
                               // cout << "fi: " << fi ;
                               PointersToHashtable[i]->InsertIntoHashtable("", NULL, NULL, euclidean[j], NULL, fi);

                            }
                        }
                        j++;
                    }
                    inputfile.close();
                    if(option == "A") 
                    {
                        string method = "@metric_space euclidean";
                        QuerySearch(argv[2], argv[10], argv[4],PointersToHashtable, L, k, method, N, NULL, NULL, euclidean, P);
                    }
                    if(option == "B") 
                    {                     
                        string method = "@metric euclidean";
                        ofstream outputFile("Results.txt");
                        Cluster **cluster = new Cluster*[k];
                        int ObjectiveFunction[k];
                        float ObjectiveFunctionF[k];
                        
                        k_medoidspp( cluster, k, N, method, NULL, NULL, euclidean, NULL);                        
                        for (i = 0; i < k; i++) cout << cluster[i]->getCentroid() << endl; 
                        
                        for (i = 0; i < k; i++) ObjectiveFunction[i] = 0;
                        for (i = 0; i < k; i++) ObjectiveFunctionF[i] = 0;

                        PAM(cluster, k, N, method, NULL, NULL, euclidean, NULL, ObjectiveFunction, ObjectiveFunctionF);
                        for (i = 0; i < k; i++) cout << ObjectiveFunction[i] << endl;

                        alalloyds(cluster, k, N, method, NULL, NULL, euclidean, NULL, ObjectiveFunction, ObjectiveFunctionF);
                        cout << "after allalalala " << endl;
                        
                        float s[k], sum = 0;
                        Silhouette(cluster,  k,  N,  method, s);
                        outputFile << "Silhouette: [ " ;
                        for (i = 0; i < k; i++)
                        {
                            sum += s[i];
                            outputFile << s[i] << " , ";
                            outputFile.flush();
                        }       
                        outputFile <<  " ] "<< endl;
                        outputFile <<  " Sum: "<< sum << endl;
                        outputFile.flush();
                        NNRMDB( k,  N,  method, cluster, 1000, NULL, NULL, euclidean, outputFile);
                        for (i = 0; i < k; i++) delete cluster[i];
                    }
                    for (i = 0; i < L; i++) delete PointersToHashtable[i];
                    for (i = 0; i < j; i++) delete euclidean[i];
                }
                break;
                default:
                    cout << "Not a Valid Choice.Choose again.\n";           
                break;
            }

        }
        
        
        
    }
    else cout << "Unable to open input file" << endl; 
    

    return 0;
}


string Rate(string rate, string method, double &average)
{
    if(method == "cosine"||method =="euclidean")
    {
        string h;
        h = rate;
        int length;
        int p=0;
        average = 0.0;
        length = h.length();
        for (int i = 0; i < length; i++) 
        {
            h = rate[i];
            if (h == "\t") {
                p++;
            }
        }
        double array[p + 1];
        istringstream iss(rate);
        for (auto& i : array) {
            iss >> i;
        }

        for(int i = 0; i < (p+1); i++ )
        {
            average = average + array[i];
        }
        average = average / p+1 ;       //R(user)

        string r, t;  
        int i;
        t = "\t";
        for (int i = 0; i < p+1; i++)
        {
            array[i] = array[i] - average;
        }
        // r = to_string(array[0]);
        double numb; 
        ostringstream convert;
        r = to_string(array[0]);
        for (i = 1; i < p+1; i++ )
        {
            numb = array[i];
            h = to_string(numb);
            r = r + t + h;
        }  
        return r;
    }
    else 
    {
        string h;
        h = rate;
        int length;
        int p=0;
        length = h.length();
        for (int i = 0; i < length; i++) 
        {
            h = rate[i];
            if (h == "\t") {
                p++;
            }
        }
        int array[p + 1];
        istringstream iss(rate);
        for (auto& i : array) {
            iss >> i;
        }

        string r, t;  
        int i;
        t = "\t";
        for (int i = 0; i < p+1; i++)
        {           
            if(array[i] <= 2)
            {
                array[i] = 0;
            }
            else
            {
                array[i] = 1;
            }
        }
        int numb; 
        r = to_string(array[0]);
        for (i = 1; i < p+1; i++ )
        {
            numb = array[i];
            h = to_string(numb);
            r = r + h;
        }
        return r; 
    }
    return 0;
}

void QuerySearch(char *tmp1, char *tmp2, char *tmp, Hashtable **PointersToHashtable, int L, int k, string method, int N, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, int P)
{
    string line, temp, neighbour, min_neighbour;
    int min, distance, radius = 1, j, i = 0;
    ofstream outputFile("ResultsNN.txt");
    vector <string> neighbours;
    clock_t start;
    double duration;
    start = clock();
    for (j = 0; j < N; j++)
    {
        //cout << "Query:   user" << j+1 << endl;
        //cout << "R-near neighbors:" << endl;
        for (i = 0; i < 1; i++)   //Search  neighbour within radius
        {
            if (method == "@metric_space hamming")
            {
                temp = hamming[j]->getId();
                RangeNeighbourSearchA(to_string(j+1), radius, PointersToHashtable[i], temp, k, L, method, N, tmp1, outputFile, neighbours, NULL);                                             
                if (neighbours.size() != 0)
                {
                    sort(neighbours.begin(), neighbours.end());
                    outputFile << "\nuser  " << j+1 << "\t";
                    NNRMDA( k,  N,  method, neighbours,  P,  1000, hamming[j], NULL, NULL, outputFile);
                }
            }                
            else if (method == "@metric_space euclidean")
            {
                temp = euclidean[j]->getId();
                RangeNeighbourSearchA(to_string(j+1), radius, PointersToHashtable[i], temp, k, L, method, N, tmp1, outputFile, neighbours, NULL);                                             
                if (neighbours.size() != 0)
                {
                    sort(neighbours.begin(), neighbours.end());
                    outputFile << "\nuser  " << j+1 << "\t";
                    NNRMDA( k,  N,  method, neighbours,  P,  1000, NULL, NULL, euclidean[j], outputFile);
                }
            }    
            else 
            {
                temp = cosine[j]->getId();

                RangeNeighbourSearchA(to_string(j+1), radius, PointersToHashtable[i], temp, k, L, method, N, tmp1, outputFile, neighbours, NULL);                                             

                if (neighbours.size() != 0)
                {
                    sort(neighbours.begin(), neighbours.end());
                    outputFile << "\nuser  " << j+1 << "\t";
                    NNRMDA( k,  N,  method, neighbours,  P,  1000, NULL, cosine[j], NULL, outputFile);
                }
                
            }    
        }
        
        neighbours.clear();
    }
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    outputFile << "Execution Time:  " << duration << endl;

}