#ifndef CSVLOGGER_H
#define CSVLOGGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class CSVLogger {
private:
    string journeyFile, stationFile;
    int journeyID;
public:
    CSVLogger(string jf="../data/journey_log.csv",
              string sf="../data/station_stats.csv")
        :journeyFile(jf),stationFile(sf),journeyID(1){
        ofstream j(journeyFile);
        if(j.is_open()){j<<"journey_id,passenger_name,from_station,to_station,distance_km,fare_rs,duration_mins,timestamp\n";j.close();}
        ofstream s(stationFile);
        if(s.is_open()){s<<"station_name,total_boardings\n";s.close();}
    }

    void logJourney(string p,string f,string t,int d,int fare,int dur){
        ofstream out(journeyFile,ios::app);
        if(!out.is_open())return;
        time_t now=time(0); tm* tm_=localtime(&now);
        char ts[20]; strftime(ts,sizeof(ts),"%Y-%m-%d %H:%M",tm_);
        out<<journeyID++<<","<<p<<","<<f<<","<<t<<","<<d<<","<<fare<<","<<dur<<","<<ts<<"\n";
        out.close();
        cout<<"  [CSV] Journey logged.\n";
    }

    void logStationFootfall(string s){
        ofstream out(stationFile,ios::app);
        if(!out.is_open())return;
        out<<s<<",1\n"; out.close();
    }
};

#endif