# Smart City Transit Optimizer

A full-stack placement portfolio project combining a C++ DSA engine, a Python/Pandas analytics pipeline, and a Power BI dashboard — built around a simulated city transit network modeled loosely on Nagpur's bus system.

The goal was to demonstrate both core data structures & algorithms knowledge and data analytics skills in one connected, end-to-end pipeline, rather than as two separate disconnected projects.

> **Note:** This project uses simulated data, not a live feed. The C++ engine generates randomized but realistic trip data, which flows through the same kind of pipeline a real-time system would use.

## Architecture

```
 C++ DSA Engine          CSV Logs           Python / Pandas         Power BI
 ───────────────    ───────────────    ──────────────────────    ──────────────
 7 station network  →  journey_log.csv  →  Peak hour analysis    →  KPI cards
 9 routes              station_stats.csv   Route efficiency         Route efficiency
 500+ simulated        delay_log.csv        score (NumPy)            bar chart
 trips                                     Fare revenue              Busiest stations
                                            breakdown                 chart
                                           Delay summary             Delay by route
                                                                       Fare revenue donut
```

## Tech stack

| Layer | Tools |
|---|---|
| Simulation engine | C++ (arrays, strings, linked lists, stacks, queues, binary search, merge sort, recursion) |
| Analytics | Python, Pandas, NumPy, Matplotlib |
| Dashboard | Power BI Desktop |
| Version control | Git, GitHub |

## DSA modules (C++ layer)

| Module | DSA Topic | What it does |
|---|---|---|
| `RouteManager` | Arrays + Strings | Stores stations and routes in a 2D adjacency matrix; string-based station search |
| `PassengerList` | Linked List | Singly linked list for boarding and alighting passengers |
| `JourneyTracker` | Stack + Queue | Stack for journey undo log (LIFO), queue for platform boarding line (FIFO) |
| `FareLookup` | Binary Search | O(log n) fare lookup from a sorted distance-fare table |
| `ScheduleSorter` | Merge Sort + STL Sort | Sorts bus schedules by arrival time and by seat availability |
| `PathFinder` | Recursion + Backtracking | DFS finds all paths between two stations, highlights the shortest |
| `TripSimulator` | Randomized generation | Auto-generates 500+ realistic passenger journeys and bus delay records |

## Analytics layer (Python)

`analytics/transit_analysis.py` reads the CSV logs produced by the C++ engine and runs:

- **Peak hour analysis** — busiest boarding hours
- **Route efficiency score** — passengers per km (NumPy-calculated)
- **Station footfall ranking** — busiest stations
- **Fare revenue breakdown** — total and % revenue per route
- **Daily demand trend** — trips per day
- **Delay summary** — average delay per route, on-time percentage

Output: three clean CSVs (`analytics_output.csv`, `station_footfall.csv`, `delay_summary.csv`) feeding directly into Power BI, plus a quick Matplotlib chart for sanity-checking the data before building the dashboard.

## Dashboard (Power BI)

`dashboard/transit_dashboard.pbix` includes:

- KPI cards — total trips, total revenue, average delay
- Route efficiency bar chart
- Busiest stations column chart
- Average delay by route bar chart
- Fare revenue by route donut chart

## Folder structure

```
SmartCityTransitOptimizer/
├── src/                      C++ source files
│   ├── main.cpp
│   ├── RouteManager.cpp / .h
│   ├── PassengerList.cpp / .h
│   ├── JourneyTracker.cpp / .h
│   ├── FareLookup.cpp / .h
│   ├── ScheduleSorter.cpp / .h
│   ├── PathFinder.cpp / .h
│   ├── TripSimulator.cpp / .h
│   └── CSVLogger.h
├── data/                      Generated CSV logs
│   ├── journey_log.csv
│   ├── station_stats.csv
│   └── delay_log.csv
├── analytics/                 Python analysis layer
│   ├── transit_analysis.py
│   ├── analytics_output.csv
│   ├── station_footfall.csv
│   ├── delay_summary.csv
│   └── eda_summary.png
├── dashboard/                 Power BI dashboard
│   ├── transit_dashboard.pbix
│   └── dashboard_screenshot.png
└── README.md
```

## How to run

### 1. C++ engine

```bash
cd src
g++ main.cpp RouteManager.cpp PassengerList.cpp JourneyTracker.cpp FareLookup.cpp ScheduleSorter.cpp PathFinder.cpp TripSimulator.cpp -o transit
./transit        # or transit.exe on Windows
```

The program loads a demo network of 7 Nagpur stations and 9 routes, then presents a menu-driven interface. Try these first:

- **Option 6** — Book a ticket: runs recursion (path finding), binary search (fare lookup), and CSV logging together
- **Option 19** — Simulate N trips: auto-generates randomized journey data
- **Option 4** — Find all paths between two stations: demonstrates DFS with backtracking

### 2. Python analytics

```bash
cd analytics
pip install pandas numpy matplotlib
python transit_analysis.py
```

### 3. Power BI dashboard

Open `dashboard/transit_dashboard.pbix` in Power BI Desktop. The data source points to the CSVs in the `analytics/` folder — re-run steps 1 and 2, then click **Refresh** in Power BI to update the dashboard with new data.

## Author

Sejal Bhupal
B.E. Computer Engineering, St. Vincent Pallotti College of Engineering & Technology, Nagpur
[GitHub](https://github.com/sejalbhupal)
