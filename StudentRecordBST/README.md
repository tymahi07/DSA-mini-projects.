# Student Record Search System Using a Binary Search Tree (C++)

DSA Mini Project – PPF Week 9 | Individual | Language: C++ (beginner level)

## About
Stores student records (enrolment ID, name, department) in a **Binary Search Tree** keyed by enrolment ID.

## Features
- Insert (duplicate IDs rejected with a clear message)
- Search by ID (also shows number of comparisons)
- Delete – leaf, one-child and two-child cases (inorder successor)
- Inorder (sorted), Preorder and Postorder traversals
- Tree shape display, height and size
- Efficiency experiment: balanced-looking vs sorted insertion
- 12 sample records pre-loaded when no data file exists; menu-driven; automated tests
- Read student records from `students_data.txt` at startup and write changes automatically

## Build & Run
```bash
g++ -o bst_students main.cpp
./bst_students          # interactive menu
./bst_students --test   # automated tests + efficiency experiment
```

## Data Storage
The program loads records from `students_data.txt` when the file exists. Otherwise, it starts with the 12 sample records. Insertions, deletions, sample-data loading, and exit save the records to the file. Each line stores `ID|Name|Department`.

## Test Cases (tree built from 50,30,70,20,40,60,80,10)
| # | Case | Expected | Result |
|---|------|----------|--------|
| 1 | Inorder | 10 20 30 40 50 60 70 80 | PASS |
| 2 | Preorder | 50 30 20 10 40 70 60 80 | PASS |
| 3 | Postorder | 10 20 40 30 60 80 70 50 | PASS |
| 4 | Duplicate ID 40 | rejected, size stays 8 | PASS |
| 5 | Search 60 / 65 | found / not found | PASS |
| 6 | Delete leaf (10) | 20 30 40 50 60 70 80 | PASS |
| 7 | Delete one-child node (20) | 10 30 40 50 60 70 80 | PASS |
| 8 | Delete two-child node (30) | 10 20 40 50 60 70 80; root's left becomes 40 | PASS |
| 9 | Delete missing ID 99 | nothing deleted | PASS |

## Efficiency Result (N = 15)
| Insertion order | Height | Insert comparisons | Avg comparisons per search |
|---|---|---|---|
| Balanced-looking (8,4,12,2,...) | 4 | 34 | 3.27 |
| Sorted (1,2,...,15) | 15 | 105 | 8.0 |

## Complexity
| Operation | Average | Worst (skewed) |
|---|---|---|
| Insert / Search / Delete | O(log n) | O(n) |
| Traversals | O(n) | O(n) |
| Space | O(n) | O(n) |

## Files
`main.cpp`, `REPORT.md`, `README.md`

## Concepts Used
`struct`, pointers (`new` / `delete`), recursion, arrays, `string`. classes, templates or STL containers.
