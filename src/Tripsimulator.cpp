#include "TripSimulator.h"
#include <cstdlib>
#include <ctime>

TripSimulator::TripSimulator(RouteManager& routeMgr, FareLookup& fareL,
                              ScheduleSorter& sched, CSVLogger& log)
    : rm(routeMgr), fl(fareL), ss(sched), logger(log) {
    srand((unsigned)time(0));   // Seed random generator once
}

// Helper: random integer between low and high (inclusive)
int TripSimulator::randomInRange(int low, int high) {
    return low + rand() % (high - low + 1);
}

// Helper: get distance between two station indices (uses RouteManager's array)
int TripSimulator::findDistanceBetween(int fromIdx, int toIdx) {
    int d = rm.getDistance(fromIdx, toIdx);
    if (d == 0) {
        // No direct route - estimate using random plausible distance
        // (keeps simulation simple without running full pathfinding each time)
        d = randomInRange(5, 20);
    }
    return d;
}

// ============================================================
//  SIMULATE TRIPS: generates N random journeys and logs to CSV
//  This is what makes journey_log.csv go from 2 rows to 500+ rows
//  -> giving the Python/Pandas layer real data to analyze in Week 3
// ============================================================
void TripSimulator::simulateTrips(int count) {
    int stationCount = rm.getStationCount();
    if (stationCount < 2) {
        cout << "  [!] Need at least 2 stations to simulate trips.\n";
        return;
    }

    cout << "\n  [i] Simulating " << count << " trips...\n";

    int logged = 0;
    for (int i = 0; i < count; i++) {
        // Pick two DIFFERENT random stations
        int fromIdx = randomInRange(0, stationCount - 1);
        int toIdx;
        do {
            toIdx = randomInRange(0, stationCount - 1);
        } while (toIdx == fromIdx);

        string passenger = sampleNames[randomInRange(0, NUM_SAMPLE_NAMES - 1)];
        string from = rm.getStationName(fromIdx);
        string to   = rm.getStationName(toIdx);

        // Distance + fare using existing modules (array lookup + binary search)
        int dist = findDistanceBetween(fromIdx, toIdx);
        int fare = fl.getFare(dist);
        int duration = dist * 3 + randomInRange(-5, 10);  // realistic variance
        if (duration < 5) duration = 5;

        // Log to CSV (bridge to Python layer)
        logger.logJourney(passenger, from, to, dist, fare, duration);
        logger.logStationFootfall(from);
        logger.logStationFootfall(to);
        logged++;

        // Progress indicator every 100 trips (avoids flooding console)
        if ((i + 1) % 100 == 0) {
            cout << "    ... " << (i + 1) << " trips simulated\n";
        }
    }

    cout << "  [+] Simulation complete: " << logged << " trips logged to journey_log.csv\n";
    cout << "  [+] Station footfall updated in station_stats.csv\n";
}

// ============================================================
//  SIMULATE DELAYS: for every bus in the schedule, generate a
//  realistic actual-arrival-time vs scheduled-time gap
//  -> writes delay_log.csv, used for the "avg delay %" KPI in Power BI
// ============================================================
void TripSimulator::simulateDelays() {
    int busCount = ss.getCount();
    if (busCount == 0) {
        cout << "  [!] No buses in schedule to simulate delays for.\n";
        return;
    }

    ofstream delayFile("../data/delay_log.csv");
    if (!delayFile.is_open()) {
        cout << "  [!] Could not create delay_log.csv\n";
        return;
    }
    delayFile << "bus_id,route_name,scheduled_time,actual_time,delay_minutes\n";

    cout << "\n  [i] Simulating delays for " << busCount << " buses...\n";

    // We need access to schedule data - use displaySchedule's data indirectly
    // Since ScheduleSorter doesn't expose individual bus getters in Week 1,
    // we simulate against bus IDs 101-107 matching loadSampleSchedule()
    int busIDs[20]    = {101,102,103,104,105,106,107};
    string routes[20] = {"Nagpur-Wardha","Nagpur-Amravati","Nagpur-Chandrapur",
                          "Nagpur-Yavatmal","Nagpur-Bramhapuri","Nagpur-Bhandara","Nagpur-Gondia"};
    int times[20]     = {1430, 900, 1200, 1615, 730, 1100, 1330};

    for (int i = 0; i < busCount && i < 7; i++) {
        int delay = randomInRange(-2, 25);  // most buses run on time or slightly late
        if (delay < 0) delay = 0;           // can't arrive "early" in this sim

        int scheduled = times[i];
        int actualHr  = scheduled / 100;
        int actualMin = (scheduled % 100) + delay;
        while (actualMin >= 60) { actualMin -= 60; actualHr++; }
        int actual = actualHr * 100 + actualMin;

        delayFile << busIDs[i] << "," << routes[i] << ","
                   << scheduled << "," << actual << "," << delay << "\n";

        cout << "    Bus " << busIDs[i] << " (" << routes[i] << "): "
             << delay << " min delay\n";
    }

    delayFile.close();
    cout << "  [+] delay_log.csv created with " << min(busCount,7) << " entries.\n";
}