#ifndef TRIPSIMULATOR_H
#define TRIPSIMULATOR_H

#include <iostream>
#include <string>
#include "RouteManager.h"
#include "FareLookup.h"
#include "ScheduleSorter.h"
#include "CSVLogger.h"
using namespace std;

// Random Indian names for simulated passengers
const int NUM_SAMPLE_NAMES = 15;

class TripSimulator {
private:
    RouteManager&   rm;
    FareLookup&     fl;
    ScheduleSorter& ss;
    CSVLogger&      logger;

    string sampleNames[NUM_SAMPLE_NAMES] = {
        "Aarav","Priya","Rohan","Sneha","Vikram","Ananya","Karan","Pooja",
        "Aditya","Neha","Sahil","Riya","Arjun","Diya","Manish"
    };

    int randomInRange(int low, int high);          // helper: random int [low,high]
    int findDistanceBetween(int fromIdx, int toIdx); // helper: distance lookup

public:
    TripSimulator(RouteManager& routeMgr, FareLookup& fareL,
                  ScheduleSorter& sched, CSVLogger& log);

    void simulateTrips(int count);     // Generate N random journeys -> CSV
    void simulateDelays();             // Generate delay_log.csv from schedule
};

#endif