#ifndef ROUTEMANAGER_H
#define ROUTEMANAGER_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_STATIONS = 10;

class RouteManager {
private:
    string stationNames[MAX_STATIONS];
    int adjMatrix[MAX_STATIONS][MAX_STATIONS];
    int stationCount;

public:
    RouteManager();
    int getStationIndex(string name);
    void addStation(string name);
    void addRoute(string from, string to, int distance);
    void displayAllRoutes();
    void displayStations();
    int getDistance(int from, int to);
    int getStationCount();
    string getStationName(int index);
    bool routeExists(int from, int to);
};

#endif