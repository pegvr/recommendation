#ifndef HAMMING_H
#define	HAMMING_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "randomfunc.h"
#include "time.h"

using namespace std;

class Hamming {
public:
    Hamming(string temp, string temp1,string items, double average);
    Hamming(const Hamming& orig);
    virtual ~Hamming();
    string ConstructGFunction(int k);
    string getId();
    string getName();
    string getItem();
    double getRu();
private:
    string id, name;
    int length;
    string item;
    double Ru;
};


#endif	/* HAMMING_H */
