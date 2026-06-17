#ifndef SCHEDULESORTER_H
#define SCHEDULESORTER_H
#include <iostream>
#include <string>
using namespace std;

const int MAX_BUSES = 20;

struct BusSchedule {
    int busID; string routeName;
    int arrivalTime; int platform; int seatsAvailable;
};

class ScheduleSorter {
private:
    BusSchedule schedule[MAX_BUSES];
    int count;
    void mergeSort(BusSchedule arr[], int l, int r);
    void merge(BusSchedule arr[], int l, int m, int r);
public:
    ScheduleSorter();
    void addBus(int id, string route, int time, int platform, int seats);
    void sortByArrival();
    void sortBySeats();
    void displaySchedule();
    void loadSampleSchedule();
    string formatTime(int t);
    int getCount();
};

#endif