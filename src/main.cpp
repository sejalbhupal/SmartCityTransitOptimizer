// ============================================================
//  SMART CITY TRANSIT OPTIMIZER
//  C++ DSA Project - Week 1 Complete
//
//  Modules:
//    RouteManager   -> Arrays + Strings
//    PassengerList  -> Linked List
//    JourneyTracker -> Stack + Queue
//    FareLookup     -> Binary Search
//    ScheduleSorter -> Merge Sort + STL Sort
//    PathFinder     -> Recursion + Backtracking (DFS)
//    CSVLogger      -> File I/O (bridge to Python layer)
//
//  Compile:
//    g++ main.cpp RouteManager.cpp PassengerList.cpp
//        JourneyTracker.cpp FareLookup.cpp
//        ScheduleSorter.cpp PathFinder.cpp -o transit
//  Run:
//    ./transit
// ============================================================

#include <iostream>
#include <string>
#include <limits>
#include "RouteManager.h"
#include "PassengerList.h"
#include "JourneyTracker.h"
#include "FareLookup.h"
#include "ScheduleSorter.h"
#include "PathFinder.h"
#include "CSVLogger.h"

using namespace std;

// --- Helpers -----------------------------------------------------------------
void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printHeader() {
    cout << "\n";
    cout << "  ====================================================\n";
    cout << "  |      SMART CITY TRANSIT OPTIMIZER  v1.0          |\n";
    cout << "  |      C++ DSA Project | sejalbhupal               |\n";
    cout << "  ====================================================\n";
}

void printMenu() {
    cout << "\n  +---------------------------------------------+\n";
    cout <<   "  |              MAIN MENU                      |\n";
    cout <<   "  +---------------------------------------------+\n";
    cout <<   "  |  ROUTE MANAGEMENT  (Arrays + Strings)       |\n";
    cout <<   "  |   1. Add station                            |\n";
    cout <<   "  |   2. Add route between stations             |\n";
    cout <<   "  |   3. Display all routes                     |\n";
    cout <<   "  +---------------------------------------------+\n";
    cout <<   "  |  JOURNEY  (Binary Search + Recursion)       |\n";
    cout <<   "  |   4. Find all paths between two stations    |\n";
    cout <<   "  |   5. Look up fare for a distance            |\n";
    cout <<   "  |   6. Book a ticket (path + fare + log CSV)  |\n";
    cout <<   "  +---------------------------------------------+\n";
    cout <<   "  |  PASSENGERS  (Linked List)                  |\n";
    cout <<   "  |   7. Board a passenger                      |\n";
    cout <<   "  |   8. Alight a passenger (by ticket ID)      |\n";
    cout <<   "  |   9. View all passengers on board           |\n";
    cout <<   "  +---------------------------------------------+\n";
    cout <<   "  |  JOURNEY TRACKER  (Stack + Queue)           |\n";
    cout <<   "  |  10. Add stop to journey log (Stack push)   |\n";
    cout <<   "  |  11. Undo last stop       (Stack pop)       |\n";
    cout <<   "  |  12. View current journey log               |\n";
    cout <<   "  |  13. Join boarding line   (Queue enqueue)   |\n";
    cout <<   "  |  14. Board next passenger (Queue dequeue)   |\n";
    cout <<   "  |  15. View boarding line                     |\n";
    cout <<   "  +---------------------------------------------+\n";
    cout <<   "  |  SCHEDULE  (Merge Sort + STL Sort)          |\n";
    cout <<   "  |  16. View bus schedule                      |\n";
    cout <<   "  |  17. Sort schedule by arrival time          |\n";
    cout <<   "  |  18. Sort schedule by seats available       |\n";
    cout <<   "  +---------------------------------------------+\n";
    cout <<   "  |   0. Exit                                   |\n";
    cout <<   "  +---------------------------------------------+\n";
    cout <<   "  Enter choice: ";
}

// --- Load demo city network (Nagpur region) -----------------------------------
void loadDemoData(RouteManager& rm, ScheduleSorter& ss, FareLookup& fl) {
    cout << "\n  [i] Loading Nagpur city transit network...\n";

    // Stations - stored in string array inside RouteManager
    rm.addStation("Nagpur Central");
    rm.addStation("Sitabuldi");
    rm.addStation("Dharampeth");
    rm.addStation("Wardha Road");
    rm.addStation("Kamptee");
    rm.addStation("Hingna");
    rm.addStation("Katol Road");

    // Routes - stored in 2D adjacency matrix
    //            from              to               distance(km)
    rm.addRoute("Nagpur Central", "Sitabuldi",       3);
    rm.addRoute("Nagpur Central", "Wardha Road",     8);
    rm.addRoute("Nagpur Central", "Kamptee",        12);
    rm.addRoute("Sitabuldi",      "Dharampeth",      4);
    rm.addRoute("Sitabuldi",      "Wardha Road",     6);
    rm.addRoute("Dharampeth",     "Hingna",          9);
    rm.addRoute("Wardha Road",    "Katol Road",     11);
    rm.addRoute("Kamptee",        "Katol Road",      7);
    rm.addRoute("Hingna",         "Katol Road",      5);

    // Bus schedule
    ss.loadSampleSchedule();

    // Fare table (sorted array for binary search)
    fl.loadDefaultFares();

    cout << "  [i] Demo network ready - 7 stations, 9 routes loaded.\n";
}

// --- MAIN ---------------------------------------------------------------------
int main() {

    // Instantiate all 6 modules
    RouteManager   rm;
    PassengerList  pl;
    JourneyStack   js;
    BoardingQueue  bq;
    FareLookup     fl;
    ScheduleSorter ss;
    PathFinder     pf(rm);   // PathFinder needs RouteManager reference
    CSVLogger      logger;

    printHeader();
    loadDemoData(rm, ss, fl);

    int choice;
    do {
        printMenu();
        cin >> choice;
        clearInput();

        switch (choice) {

        // -- MODULE 1: ROUTE MANAGER (Arrays + Strings) -----------------------

        case 1: {
            cout << "  Enter station name: ";
            string name; getline(cin, name);
            rm.addStation(name);
            break;
        }

        case 2: {
            cout << "  Enter FROM station: ";
            string from; getline(cin, from);
            cout << "  Enter TO station  : ";
            string to; getline(cin, to);
            cout << "  Enter distance (km): ";
            int dist; cin >> dist; clearInput();
            rm.addRoute(from, to, dist);
            break;
        }

        case 3: {
            rm.displayStations();
            rm.displayAllRoutes();
            break;
        }

        // -- MODULE 6: PATH FINDER (Recursion + Backtracking) -----------------

        case 4: {
            rm.displayStations();
            cout << "  Enter FROM station: ";
            string from; getline(cin, from);
            cout << "  Enter TO station  : ";
            string to; getline(cin, to);
            pf.findAllPaths(from, to);
            break;
        }

        // -- MODULE 4: FARE LOOKUP (Binary Search) ----------------------------

        case 5: {
            fl.displayFareTable();
            cout << "\n  Enter distance (km): ";
            int d; cin >> d; clearInput();
            int fare = fl.getFare(d);
            if (fare > 0)
                cout << "  [i] Fare for " << d << " km = Rs " << fare << "\n";
            break;
        }

        // -- BOOK TICKET: PathFinder + FareLookup + CSVLogger -----------------
        // This is your STAR feature - combines 3 modules in one flow

        case 6: {
            rm.displayStations();
            cout << "  Passenger name    : ";
            string name; getline(cin, name);
            cout << "  FROM station      : ";
            string from; getline(cin, from);
            cout << "  TO station        : ";
            string to; getline(cin, to);

            // Step 1: Find path using recursion
            pf.findAllPaths(from, to);

            // Step 2: Get station indices for distance lookup
            int fi = rm.getStationIndex(from);
            int ti = rm.getStationIndex(to);
            if (fi == -1 || ti == -1) {
                cout << "  [!] Invalid station(s).\n";
                break;
            }
            int dist = rm.getDistance(fi, ti);
            if (dist == 0) {
                cout << "  [!] No direct route - showing distance as 10 km.\n";
                dist = 10;
            }

            // Step 3: Binary search for fare
            int fare = fl.getFare(dist);
            cout << "\n  -- Ticket Summary ----------------------\n";
            cout << "  Passenger : " << name   << "\n";
            cout << "  Route     : " << from   << " -> " << to << "\n";
            cout << "  Distance  : " << dist   << " km\n";
            cout << "  Fare      : Rs " << fare << "\n";
            cout << "  ----------------------------------------\n";

            // Step 4: Log to CSV (bridge to Python analytics layer)
            logger.logJourney(name, from, to, dist, fare, dist * 3);
            logger.logStationFootfall(from);
            logger.logStationFootfall(to);

            // Step 5: Board into passenger linked list
            pl.boardPassenger(name, to);
            break;
        }

        // -- MODULE 2: PASSENGER LIST (Linked List) ----------------------------

        case 7: {
            cout << "  Passenger name   : ";
            string name; getline(cin, name);
            cout << "  Destination      : ";
            string dest; getline(cin, dest);
            pl.boardPassenger(name, dest);
            break;
        }

        case 8: {
            pl.displayAll();
            cout << "  Enter Ticket ID to alight: ";
            int id; cin >> id; clearInput();
            pl.alightPassenger(id);
            break;
        }

        case 9: {
            pl.displayAll();
            break;
        }

        // -- MODULE 3: JOURNEY TRACKER - STACK (LIFO) -------------------------

        case 10: {
            cout << "  Enter stop name: ";
            string stop; getline(cin, stop);
            js.push(stop);
            js.peek();
            break;
        }

        case 11: {
            js.pop();
            js.peek();
            break;
        }

        case 12: {
            js.displayAll();
            break;
        }

        // -- MODULE 3: JOURNEY TRACKER - QUEUE (FIFO) -------------------------

        case 13: {
            cout << "  Passenger name: ";
            string name; getline(cin, name);
            bq.enqueue(name);
            break;
        }

        case 14: {
            bq.dequeue();
            bq.displayLine();
            break;
        }

        case 15: {
            bq.displayLine();
            break;
        }

        // -- MODULE 5: SCHEDULE SORTER (Merge Sort + STL) ---------------------

        case 16: {
            ss.displaySchedule();
            break;
        }

        case 17: {
            ss.sortByArrival();       // Merge Sort
            ss.displaySchedule();
            break;
        }

        case 18: {
            ss.sortBySeats();         // STL sort + lambda comparator
            ss.displaySchedule();
            break;
        }

        case 0: {
            cout << "\n  [i] Exiting. CSV logs saved to data/ folder.\n";
            cout << "  [i] Run analytics/transit_analysis.py next for Python layer.\n\n";
            break;
        }

        default:
            cout << "  [!] Invalid choice. Enter 0-18.\n";
        }

    } while (choice != 0);

    return 0;
}