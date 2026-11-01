# DSA Mini Projects in C++

A collection of beginner-friendly **Data Structures and Algorithms (DSA) mini projects** developed using C++. These projects demonstrate the practical implementation of fundamental data structures, algorithms, file handling, and problem-solving techniques.

## 📌 Projects Included

### 1. Campus Route Finder – Graphs (BFS & DFS)

A campus navigation system that represents campus locations as vertices and walking paths as edges in an undirected graph.

**Features:**
- Add and display campus locations.
- Add connections between locations.
- Graph representation using Adjacency List and Adjacency Matrix.
- Find the shortest route using Breadth-First Search (BFS).
- Explore locations using Depth-First Search (DFS).
- Check connectivity and unreachable locations.
- Identify connected components.
- Read and write campus data using file handling.
- Built-in test cases.

**Data Structure:** Graph  
**Algorithms:** BFS and DFS

### 2. Student Record Search System – Binary Search Tree (BST)

A student record management system that stores and manages student information using a Binary Search Tree based on enrolment IDs.

**Features:**
- Insert new student records.
- Search students using enrolment ID.
- Delete student records.
- Handle duplicate enrolment IDs.
- Display records in sorted order using Inorder Traversal.
- Preorder and Postorder Traversals.
- Display tree structure, height, and total number of records.
- Compare balanced and sorted insertion orders.
- Read and write student records using file handling.
- Built-in automated test cases.

**Data Structure:** Binary Search Tree (BST)  
**Algorithms:** Insertion, Searching, Deletion, and Tree Traversals.

## 🛠️ Technologies Used

- **Programming Language:** C++
- **Concepts:** Data Structures and Algorithms
- Graphs
- Binary Search Trees
- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Recursion
- Pointers
- File Handling
- Arrays and Strings
- Time and Space Complexity Analysis

## 📂 Repository Structure

```text
DSA-Mini-Projects-CPP/
│
├── CampusRouteFinder/
│   ├── main.cpp
│   └── README.md
│
├── StudentRecordBST/
│   ├── main.cpp
│   └── README.md
│
└── README.md
```

## ⚙️ Installation and Execution

### Prerequisites
- A C++ compiler (GCC/G++).
- Visual Studio Code, Code::Blocks, or any C++ IDE.

### 1. Clone the Repository

```bash
git clone <YOUR-GITHUB-REPOSITORY-URL>
```

### 2. Navigate to the Project Folder

For Campus Route Finder:

```bash
cd CampusRouteFinder
```

Compile and execute:

```bash
g++ main.cpp -o route_finder
./route_finder
```

Run automated tests:

```bash
./route_finder --test
```

For Student Record BST:

```bash
cd StudentRecordBST
```

Compile and execute:

```bash
g++ main.cpp -o bst_students
./bst_students
```

Run automated tests:

```bash
./bst_students --test
```

*For Windows, execute the generated `.exe` files instead of using `./`.*

## 💾 File Handling

Both projects support persistent data storage using text files.

| Project | Data File |
|---|---|
| Campus Route Finder | `campus_data.txt` |
| Student Record BST | `students_data.txt` |

The programs load previously saved data when available and save changes so that records can be maintained between executions.

## 📊 Data Structure Complexity

### Graph (Campus Route Finder)

| Operation | Adjacency List | Adjacency Matrix |
|---|---|---|
| Space | O(V + E) | O(V²) |
| BFS / DFS | O(V + E) | O(V²) |
| Edge Checking | O(degree) | O(1) |

### Binary Search Tree (Student Record System)

| Operation | Average Case | Worst Case |
|---|---|---|
| Insertion | O(log n) | O(n) |
| Searching | O(log n) | O(n) |
| Deletion | O(log n) | O(n) |
| Traversal | O(n) | O(n) |

## 🎯 Learning Objectives

These projects demonstrate how theoretical DSA concepts can be applied to practical applications.

- Understanding graph representation and traversal.
- Implementing BFS and DFS algorithms.
- Understanding Binary Search Tree operations.
- Managing dynamic memory using pointers.
- Implementing file input/output operations.
- Comparing algorithm efficiency.
- Understanding time and space complexity.
- Writing and executing test cases.

## 👨‍💻 Project Information

**Project Type:** DSA Mini Projects  
**Language:** C++  
**Level:** Beginner  
**Focus:** Practical Implementation of Data Structures and Algorithms

## 📜 License

This project is available for educational and learning purposes. Feel free to explore, learn, and improve the implementations.
   
