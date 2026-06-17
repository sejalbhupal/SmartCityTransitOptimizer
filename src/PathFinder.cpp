#include "PathFinder.h"

PathFinder::PathFinder(RouteManager& r):rm(r){reset();}

void PathFinder::reset(){
    pathLen=pathCount=bestLen=0; bestDist=999999;
    for(int i=0;i<MAX_STATIONS;i++) visited[i]=false;
    for(int i=0;i<MAX_ROUTE_PATH;i++) path[i]=bestPath[i]=-1;
}

void PathFinder::dfs(int cur,int dest){
    visited[cur]=true; path[pathLen++]=cur;

    if(cur==dest){
        pathCount++;
        int d=0;
        for(int i=0;i<pathLen-1;i++) d+=rm.getDistance(path[i],path[i+1]);
        cout<<"\n  Path "<<pathCount<<" ("<<pathLen-1<<" stops, "<<d<<" km): ";
        for(int i=0;i<pathLen;i++){
            cout<<rm.getStationName(path[i]);
            if(i<pathLen-1)cout<<" -> ";
        }
        if(d<bestDist){
            bestDist=d; bestLen=pathLen;
            for(int i=0;i<pathLen;i++) bestPath[i]=path[i];
        }
    } else {
        for(int next=0;next<rm.getStationCount();next++)
            if(!visited[next]&&rm.routeExists(cur,next))
                dfs(next,dest);
    }
    // BACKTRACK
    visited[cur]=false; pathLen--;
}

void PathFinder::findAllPaths(string from,string to){
    int src=rm.getStationIndex(from);
    int dst=rm.getStationIndex(to);
    if(src==-1){cout<<"  [!] Station '"<<from<<"' not found.\n";return;}
    if(dst==-1){cout<<"  [!] Station '"<<to<<"' not found.\n";return;}
    if(src==dst){cout<<"  [!] Same station.\n";return;}
    reset();
    cout<<"\n  === All Paths: "<<from<<" -> "<<to<<" ===";
    dfs(src,dst);
    if(!pathCount){cout<<"\n  [!] No path found.\n";return;}
    cout<<"\n\n  BEST: "<<bestDist<<" km: ";
    for(int i=0;i<bestLen;i++){
        cout<<rm.getStationName(bestPath[i]);
        if(i<bestLen-1)cout<<" -> ";
    }
    cout<<"\n  Total paths: "<<pathCount<<"\n";
}