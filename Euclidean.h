#ifndef EUCLIDEAN_H
#define	EUCLIDEAN_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <sstream>

using namespace std;

class Euclidean {
public:
    Euclidean(string temp, string temp1, string items, double Ru);
    Euclidean(const Euclidean& orig);
    virtual ~Euclidean();
    int ConstructFiFunctionC(int L, int k);
    string getId();
    string getName();
    string getRatedItems();
    double getRu();
private:
    string id, name;
    int length;
    int euclideanid;
    string item;
    double Ru;
};

#endif	/* EUCLIDEAN_H */

