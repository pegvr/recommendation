#include "CosineSim.h"

CosineSim::CosineSim(string temp, string temp1, string items, double average) {
    name = temp1; //Name = itemY
    id = temp; //id = distances from other items
    rateditems = items;
    length = id.length();
    Ru = average;           //mesh timh twn aksiologhsewn
}

CosineSim::CosineSim(const CosineSim& orig) {
}

CosineSim::~CosineSim() {
    //cout << "Cosine is destroyed" << endl;
}

string CosineSim::getId() {
    return id;
}

string CosineSim::getName() {
    return name;
}

string CosineSim::getRatedItems()
{
    return rateditems;
}

double CosineSim::getRu()
{
    return Ru;
}

string CosineSim::ConstructGFunctionC(int k) {
    int i, p = 0;
    double r, res;
    string h;
    for (i = 0; i < length; i++) //Count how many distances from other items the point has
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

    string g;
    int j;
    for (j = 0; j < k; j++) {
        r = marsagliarandom(j);
        for (int i = 0; i < (p + 1); i++)

            res += array[i] * r;

        if (res >= 0)
            g = g + "0";

        else
            g = g + "1";

    }
    r = 0;

    return g;
}