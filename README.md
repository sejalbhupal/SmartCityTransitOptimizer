# Smart City Transit Optimizer

A C++ DSA-powered transit simulation system for a city's bus and metro network — built as a placement portfolio project combining core data structures, algorithm design, and a real-world domain (urban transit).

This project is being built in 4 weekly phases: a C++ DSA engine (Weeks 1–2), a Python/Pandas analytics layer (Week 3), and a Power BI dashboard (Week 4).

## Project goal

Real transit systems — like Nagpur Metro or city bus networks — need software to manage routes, passengers, schedules, and fares. This project simulates that software at a small scale, using each core DSA topic as a real feature rather than an abstract exercise.

## Architecture

```
C++ DSA Engine  -->  CSV Logs  -->  Python/Pandas Analytics  -->  Power BI Dashboard
  (Weeks 1-2)        (bridge)           (Week 3)                    (Week 4)
```

## Tech stack

- **C++** — core simulation engine (arrays, strings, linked lists, stacks, queues, binary search, sorting, recursion)
- **Python / Pandas / NumPy** — analytics layer (Week 3)
- **Power BI** — dashboard and visualization (Week 4)
- **Git / GitHub** — version control

## Progress

### Week 1 — Core DSA modules (complete)

| Module | DSA Topic | Description |
|---|---|---|
| `RouteManager` | Arrays + Strings | Stores stations and routes using a 2D adjacency matrix and string array |
| `PassengerList` | Linked List | Singly linked list for boarding/alighting passengers |
| `JourneyTracker` | Stack + Queue | Stack for journey undo log, queue for platform boarding line |
| `FareLookup` | Binary Search | O(log n) fare lookup from a sorted distance-fare table |
| `ScheduleSorter` | Merge Sort + STL Sort | Sorts bus schedules by arrival time and seat availability |
| `PathFinder` | Recursion + Backtracking | DFS finds all paths between two stations, highlights the shortest |

### Week 2 — Data simulation layer (complete)

| Module | Purpose |
|---|---|
| `TripSimulator` | Auto-generates 500+ randomized passenger journeys to populate CSV logs |
| Delay simulator | Generates realistic scheduled-vs-actual arrival time gaps for each bus |

After Week 2, the system has generated:
- 500+ rows in `journey_log.csv`
- 1000+ rows in `station_stats.csv` (station footfall)
- 7 rows in `delay_log.csv` (bus delay records)

### Week 3 — Python analytics layer (in progress)

Planned: peak-hour demand analysis, route efficiency scoring, fare revenue breakdown, and a clean aggregated CSV export for Power BI.

### Week 4 — Power BI dashboard (upcoming)

Planned: KPI cards, hourly demand heatmap, route efficiency chart, top stations, and route/date slicers.

## Folder structure

```
SmartCityTransitOptimizer/
├── src/                     C++ source files (the DSA engine)
│   ├── main.cpp
│   ├── RouteManager.cpp / .h
│   ├── PassengerList.cpp / .h
│   ├── JourneyTracker.cpp / .h
│   ├── FareLookup.cpp / .h
│   ├── ScheduleSorter.cpp / .h
│   ├── PathFinder.cpp / .h
│   ├── TripSimulator.cpp / .h
│   └── CSVLogger.h
├── data/                    Generated CSV logs (bridge to Python)
│   ├── journey_log.csv
│   ├── station_stats.csv
│   └── delay_log.csv
├── analytics/               Python analysis scripts (Week 3)
├── dashboard/                Power BI file (Week 4)
└── README.md
```

## How to run

```bash
cd src
g++ main.cpp RouteManager.cpp PassengerList.cpp JourneyTracker.cpp FareLookup.cpp ScheduleSorter.cpp PathFinder.cpp TripSimulator.cpp -o transit
./transit        # or transit.exe on Windows
```

The program loads a demo network of 7 Nagpur stations with 9 routes and a 7-bus schedule, then presents a menu-driven interface covering all modules.

### Try these first

- **Option 6** — Book a ticket: runs recursion (path finding), binary search (fare lookup), and CSV logging together in one flow
- **Option 19** — Simulate N trips: auto-generates randomized journey data
- **Option 4** — Find all paths between two stations: demonstrates DFS with backtracking

## Author

Sejal Bhupal
[GitHub](https://github.com/sejalbhupal) · [LinkedIn](https://linkedin.com/in/sejal-bhupal)