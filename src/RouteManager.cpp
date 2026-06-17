#include "RouteManager.h"

RouteManager::RouteManager() {
    stationCount = 0;
    for (int i = 0; i < MAX_STATIONS; i++) {
        stationNames[i] = "";
        for (int j = 0; j < MAX_STATIONS; j++)
            adjMatrix[i][j] = 0;
    }
}

int RouteManager::getStationIndex(string name) {
    for (int i = 0; i < stationCount; i++)
        if (stationNames[i] == name) return i;
    return -1;
}

void RouteManager::addStation(string name) {
    if (stationCount >= MAX_STATIONS) { cout << "  [!] Station limit reached.\n"; return; }
    if (getStationIndex(name) != -1)  { cout << "  [!] Station already exists.\n"; return; }
    stationNames[stationCount++] = name;
    cout << "  [+] Station '" << name << "' added.\n";
}

void RouteManager::addRoute(string from, string to, int distance) {
    int f = getStationIndex(from), t = getStationIndex(to);
    if (f==-1||t==-1) { cout << "  [!] Station not found.\n"; return; }
    adjMatrix[f][t] = adjMatrix[t][f] = distance;
    cout << "  [+] Route: " << from << " <--> " << to << " (" << distance << " km)\n";
}

void RouteManager::displayAllRoutes() {
    cout << "\n  === Route Network ===\n";
    for (int i = 0; i < stationCount; i++)
        for (int j = i+1; j < stationCount; j++)
            if (adjMatrix[i][j]>0)
                cout << "    " << stationNames[i] << " <--> "
                     << stationNames[j] << " : " << adjMatrix[i][j] << " km\n";
}

void RouteManager::displayStations() {
    cout << "\n  === Stations ===\n";
    for (int i = 0; i < stationCount; i++)
        cout << "    [" << i << "] " << stationNames[i] << "\n";
}

int    RouteManager::getDistance(int f,int t)  { return adjMatrix[f][t]; }
int    RouteManager::getStationCount()          { return stationCount; }
string RouteManager::getStationName(int i)      { return (i>=0&&i<stationCount)?stationNames[i]:"?"; }
bool   RouteManager::routeExists(int f,int t)   { return adjMatrix[f][t]>0; }