#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "RouteManager.h"
#include <iostream>
#include <string>
using namespace std;

const int MAX_ROUTE_PATH = 10;

class PathFinder {
private:
    RouteManager& rm;
    bool visited[MAX_STATIONS];
    int  path[MAX_ROUTE_PATH];
    int  pathLen, pathCount;
    int  bestPath[MAX_ROUTE_PATH];
    int  bestLen, bestDist;
    void dfs(int current, int destination);
public:
    PathFinder(RouteManager& r);
    void findAllPaths(string from, string to);
    void reset();
};

#endif