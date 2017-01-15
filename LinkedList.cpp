#include "LinkedList.h"
#include "Distances.h"
#include "Euclidean.h"
#include "Hamming.h"
#include <vector>

LinkedList::LinkedList()            //Linked List Constructor
{
    head = new Point;
    head->next = NULL;
    length = 0;
}

LinkedList::LinkedList(const LinkedList& orig) {
}
 

LinkedList::~LinkedList()       //Linked List Destructor
{
    Point * p = head;
    Point * q = head;
    while (q != NULL)
    {
        p = q;
        q = p -> next;
        if (q != NULL) delete p;
    }
}

// Inserts an item at the head of the list.
void LinkedList::insertPoint( Hamming * HammingPoint,CosineSim *CosinePoint,Euclidean *EuclideanPoint, int * Row)
{
    Point *temp = new Point(HammingPoint, CosinePoint, EuclideanPoint, Row);
    if (!head -> next)              //If list is empty insert here
    {
        head -> next = temp;
        length++;
        return;
    }
    temp->next = head->next;
    head->next = temp;
    length++;
}



void LinkedList::SearchA(int radius, string temp,string item, int counter, int * Row, string method, ofstream& file, int columns, vector <string> &neighbours)
{
    int i = 0;
    if (length == 0)                //There are no points in bucket for searching
    {
        //cout << "\n bucket empty \n";
        return;
    }

    Point * p = head->next;             //Start searching whole bucket for neighbour
    while (p)
    {
        if (method == "@metric_space hamming")              //Choose method
        {
            
            int diff = 0;
            string temp2 = p->hamming_key->getId();
            for (int i = 0; i < temp.size() ; i++)          //Find how many bits are different
                if (temp[i] != temp2[i]) diff++;
            if (diff < radius)   //If we found wanted distance print into file
                neighbours.push_back(p->hamming_key->getItem());
        }
        else if (method == "@metric_space euclidean")   //Choose method
        {
            float distf = DistanceEuclidean(p->euclidean_key->getId(),temp);           
            if (distf < radius)                         //Check if wanted distance has been found
                neighbours.push_back(p->euclidean_key->getRatedItems());
        }
        else if (method == "@metric_space cosine")          //Cosine method 
        {
            int dist = DistanceEuclidean(p->cosine_key->getId(),temp);
            if (dist < radius)
                neighbours.push_back(p->cosine_key->getRatedItems());
        }
        else
        {       
            cout << "Something went wrong!" << endl;
        }
        p = p->next;
    }
}

void LinkedList::SearchB(int radius, string temp, string item, int counter, int * Row, string method, ofstream& file, int columns, Cluster ** cluster, int k)
{
    int i = 0;
    if (length == 0)                //There are no points in bucket for searching
    {
        //cout << "\n bucket empty \n";
        return;
    }

    Point * p = head->next;             //Start searching whole bucket for neighbour
    while (p)
    {
        if (method == "@metric_space hamming")              //Choose method
        {
            int diff = 0;
            string temp2 = p->hamming_key->getId();
            for (int i = 0; i < temp.size() ; i++)          //Find how many bits are different
                if (temp[i] != temp2[i]) diff++;
            if (diff < radius)   
            {                           //If we found wanted distance print into file
                if(p->flag < 0) p->flag = k;
                else
                {
                    int tmp_cluster = MinDistance(p->hamming_key->getId(), cluster[k]->getCentroid(),cluster[p->flag]->getCentroid(), NULL, method);
                    if (tmp_cluster == 1)   p->flag = k;
                   
                }
            }
        }
        else if (method == "@metric euclidean")   //Choose method
        {
            float distf = DistanceEuclidean(p->euclidean_key->getId(),temp);
            
            if (distf < radius) //Check if wanted distance has been found
            {
                if(p->flag < 0) p->flag = k;
                else
                {
                    int tmp_cluster = MinDistance(p->euclidean_key->getId(), cluster[k]->getCentroid(),cluster[p->flag]->getCentroid(), NULL, method);
                    if (tmp_cluster == 1)   p->flag = k;  
                }             
            }
        }
        else if (method == "@metric cosine")          //Cosine method 
        {
            float distf = DistanceEuclidean(p->cosine_key->getId(),temp);
            if (distf < radius)
            {
                if(p->flag < 0) p->flag = k;
                else
                {
                    int tmp_cluster = MinDistance(p->cosine_key->getId(), cluster[k]->getCentroid(),cluster[p->flag]->getCentroid(), NULL, method);
                    if (tmp_cluster == 1)   p->flag = k;  
                }   
            } 
        }
        else
        {       
            int j;                                      

                    if(p->row[i] < radius && p->row[i] > 0 )
                    {
                        for ( j = 0; j < columns; j++){
                            if (p->row[j] == 0){
                                file << "item" << j+1 << endl;
                                break;
                            }
                        }
                    }
        }
        p = p->next;
    }
}



void LinkedList::printList(string method, int counter)      //Print whole bucket
{

    if (length == 0)
    {
        cout << "\n{ }\n";
        return;
    }
    Point * p = head->next;
    cout << "\n{ ";
    while (p)
    {
        if (method == "@metric_space hamming")
            cout << p->hamming_key->getId();
        else if (method == "@metric_space cosine")
            cout << p->cosine_key->getId();
        else if (method == "@metric_space euclidean")
            cout << p -> euclidean_key->getId();
        else
            for (int i = 0; i < counter; i++)
                cout << p->row[i]<< "\t";
        if (p -> next) cout << ", ";
        else break;
        p = p->next;
    }
    cout << "}\n";
}

// Returns the length of the list.
int LinkedList::getLength()
{
    return length;
}

//NN_Search same as Search function with only difference that looks for min distance
string LinkedList::NN_Search(int L, int radius, string temp,string item, Euclidean *EuclideanPoint, int * Row, string method, int &distance)
{
    int MAX= 1000;
    int i; 
    string b;
    //for (i = 0; i < L; i++)
    //{
        if (length == 0)
        {
            //cout << "\n bucket empty \n";
            return b;
        }
        Point * p = head->next;
        while (p)
        {
            if (method == "@metric_space hamming")
            {
                int diff = 0;
                string temp2 = p->hamming_key->getId();

                for (int i = 0; i < temp.size(); i++)
                    if (temp[i] != temp2[i]) diff++;
                if (diff < MAX)                         //Looks for min hamming distance
                {
                    b = p->hamming_key->getName();
                    distance = diff;
                    MAX = diff;
                }
            }
            else if (method == "@metric_space euclidean")
            {
                int num = 0, sum = 0;
                string temp2 = p->euclidean_key->getId(), h;
                for(i = 0; i < length; i++)
                {
                    h = temp2[i];
                    if(h == "\t")   num++;
                }
                double array1[num + 1];
                istringstream iss(temp2);
                for (auto& i : array1)
                {
                    iss>> i;
                }
                double array2[num + 1];
                istringstream iss2(temp);
                for (auto& i : array2)
                {
                    iss2>> i;
                }
                for (int i = 0; i < num + 1 ; i++)
                    sum += (array1[i] - array2[i]) * ((array1[i] - array2[i]));

                if (sqrt(sum) < MAX)                    //Looks for min euclidean distance
                {
                    b = p->euclidean_key->getName();
                    distance = sqrt(sum);
                    MAX = sqrt(sum);
                    if (p->next == NULL) return b;
                }
                
            }
            else if (method == "@metric_space cosine")
            {
                int num = 0, norma1 = 0, norma2 = 0, inner_product = 0;
                string temp2 = p->cosine_key->getId(), h;
                for(i = 0; i < length; i++)
                {
                    h = temp2[i];
                    if(h == "\t")   num++;
                }
                double array1[num + 1];
                std :: istringstream iss(temp2);
                for (auto& i : array1)
                {
                    iss>> i;
                }
                for(i = 0; i < num + 1; i++)
                    norma1 += array1[i] * array1[i];           //norma
                norma1 = sqrt(norma1);
                double array2[num + 1];
                istringstream iss2(temp);
                for (auto& i : array2)
                {
                    iss2>> i;
                }
                for(i = 0; i < num + 1; i++)
                    norma2 += array2[i] * array2[i];        //norma 
                norma2 = sqrt(norma2); 
                for(i = 0; i < num + 1; i++)
                    inner_product += array1[i] * array2[i];             //inner product
                int dist = 1 - (inner_product / (norma1 * norma2));     //Cosine distance
                
                if (dist < MAX)                             //Looks for min cosine distance
                {
                    b = p->cosine_key->getName();
                    MAX = dist;
                    distance = dist;
                    if (p->next == NULL) return b;
                }
                    
            }
            else
            {
                //.......
                return b;
            }
                
            p = p->next;

        }
    //}
    return b;
}


void LinkedList::AssignCluster(Cluster **cluster, string method,int k)
{
    int i = 0, dist, min_dist;
    float distf;
    if (length == 0)                //There are no points in bucket for searching
    {
        //cout << "\n bucket empty \n";
        return;
    }

    Point * p = head->next;             //Start searching whole bucket for neighbour
    while (p)
    {
        if (p->flag < 0)
        {
            int min_dist = 100000;
            float min_distf = 100000.0;
            for(int j = 0; j < k; j++)
            {
                if (method == "@metric_space hamming")
                {
                    dist = DistanceHamming(cluster[j]->getCentroid(), p->hamming_key->getId());

                }                
                else if (method == "@metric euclidean")
                {
                    distf = DistanceEuclidean(p->euclidean_key->getId(), cluster[j]->getCentroid());
                }
                else if (method == "@metric cosine")
                {

                    distf = DistanceEuclidean(p->cosine_key->getId(), cluster[j]->getCentroid());
                }
                else
                {   
                    int *row = cluster[j]->GetPointD(i);
                    dist = row[j];
                }  
                if ((dist < min_dist && dist != 0) || (distf < min_distf && distf != 0))
                {
                    min_dist = dist;
                    min_distf = distf;
                    p->flag = j;
                }  
            }
        }
        p = p->next;
    }
}

void LinkedList::CreateRealCluster(Cluster **cluster, string method, int k)
{
    int dist, min_dist, min_k;
    float distf;
    if (length == 0)                //There are no points in bucket for searching
    {
        //cout << "\n bucket empty \n";
        return;
    }

    Point * p = head->next;             //Start searching whole bucket for neighbour
    while (p)
    { 
        if (method == "@metric_space hamming")
        {
            dist = DistanceHamming(cluster[p->flag]->getCentroid(), p->hamming_key->getId());
            cluster[p->flag]->InsertPointH(p->hamming_key, dist);
            min_dist = 10000;
            int sc;
            for (int t = 0; t < k; t++)
            {
                if (t != p->flag)
                {

                    dist = DistanceHamming(cluster[t]->getCentroid(), p->hamming_key->getId());
                    if (dist < min_dist && dist != 0)
                    {
                        min_dist = dist;
                        sc = t;
                    }  
                }
            }
            cluster[p->flag]->SecondCentroid(sc, min_dist);
        }                
        else if (method == "@metric euclidean")
        {
            distf = DistanceEuclidean(p->euclidean_key->getId(),cluster[p->flag]->getCentroid());
            cluster[p->flag]->InsertPointE(p->euclidean_key, distf);
            float min_distf = 10000.0;
            int sc;
            for (int t = 0; t < k; t++)
            {
                if (t != p->flag)
                {

                    distf = DistanceEuclidean(cluster[t]->getCentroid(), p->euclidean_key->getId());
                    if (distf < min_distf && distf != 0)
                    {
                        min_distf = distf;
                        sc = t;
                    }  
                }
            }
            cluster[p->flag]->SecondCentroid(sc, min_distf);
        }
        else if (method == "@metric cosine")
        {
            distf = DistanceEuclidean(p->cosine_key->getId(), cluster[p->flag]->getCentroid());
            cluster[p->flag]->InsertPointC(p->cosine_key, distf);
            float min_distf = 10000.0;
            int sc;
            for (int t = 0; t < k; t++)
            {
                if (t != p->flag)
                {

                    distf = DistanceEuclidean(cluster[t]->getCentroid(), p->cosine_key->getId());
                    if (distf < min_distf && distf != 0)
                    {
                        min_distf = distf;
                        sc = t;
                    }  
                }
            }
            cluster[p->flag]->SecondCentroid(sc, min_distf);
        }
        else
        {   
            int *row = cluster[p->flag]->GetPointD(p->flag);
            dist = row[p->flag];
            cluster[p->flag]->InsertPointD(row, dist);
        }  
        p = p->next;
    }
}