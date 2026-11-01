# Campus Route Finder Using Graphs (C++)

DSA Mini Project – PPF Week 9 | Individual | Language: C++ (beginner level)

## About
Models a campus as an **unweighted, undirected graph** (locations = vertices, walkable paths = edges) and finds routes using **BFS** and **DFS**.

## Features
- 10 campus locations (8 connected + a 2-location "Hostel – Sports Ground" island to demonstrate disconnected components)
- Adjacency **list** (primary) and adjacency **matrix** (comparison)
- **BFS** shortest route (minimum edges) with parent-array path reconstruction
- **DFS** – recursive and iterative (explicit stack) traversal; reachability check
- Reachable / unreachable locations and connected components
- Add new locations and paths at run-time
- Read saved campus locations and paths from `campus_data.txt` at startup; write changes automatically
- Built-in test cases (expected vs actual)

## Build & Run
```bash
g++ -o route_finder main.cpp
./route_finder          # interactive menu
./route_finder --test   # run automated test cases only
```

## Data Storage
The program loads `campus_data.txt` when it exists. If the file is missing, the sample campus is used. New locations and paths are saved automatically, and the data is saved again on exit.

## Sample Run
```
Choice: 4   Source: Main Gate   Destination: Lab
Shortest route (3 step(s)): Main Gate -> Library -> Block 1 -> Lab
```

## Test Cases
| # | Case | Input | Expected | Result |
|---|------|-------|----------|--------|
| 1 | Direct route | Main Gate → Library | Main Gate -> Library | PASS |
| 2 | Multi-stop | Main Gate → Lab | Main Gate -> Library -> Block 1 -> Lab | PASS |
| 3 | Unreachable | Main Gate → Hostel | No route | PASS |
| 4 | Same node | Cafeteria → Cafeteria | Cafeteria | PASS |
| 5 | Inside island | Hostel → Sports Ground | Hostel -> Sports Ground | PASS |

## Complexity
| | Adjacency List | Adjacency Matrix |
|---|---|---|
| Space | O(V + E) | O(V²) |
| BFS / DFS time | O(V + E) | O(V²) |
| Edge check (u,v) | O(deg(u)) | O(1) |
| List neighbours of u | O(deg(u)) | O(V) |

BFS/DFS extra space: O(V) (visited + queue/stack/recursion + parent array).

## Files
- `main.cpp` – complete source code
- `REPORT.md` – short project report
- `README.md` – this file

## Screenshots to take (for submission)
Menu options 2/3 (graph), 4 (BFS route), 5 (DFS), 7/8 (reachability), and `./route_finder --test`.

## Concepts Used (all beginner level)
Global arrays, functions, loops, `string`, recursion (DFS only). No vectors, classes, templates or STL containers: the BFS queue and DFS stack are plain arrays.
