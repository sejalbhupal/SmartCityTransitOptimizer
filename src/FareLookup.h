#ifndef FARELOOKUP_H
#define FARELOOKUP_H
#include <iostream>
using namespace std;

const int MAX_FARE_ENTRIES = 20;

struct FareSlab { int maxKm; int baseFare; };

class FareLookup {
private:
    FareSlab fareTable[MAX_FARE_ENTRIES];
    int entryCount;
public:
    FareLookup();
    void loadDefaultFares();
    int  getFare(int distanceKm);
    void displayFareTable();
};

#endif