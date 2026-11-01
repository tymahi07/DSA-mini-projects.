
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>      
using namespace std;

const int MAX = 20;                 


int V = 0;                          
string names[MAX];                  
int adjList[MAX][MAX];              
int degree[MAX];                    
int adjMatrix[MAX][MAX];            


int order[MAX];                     
int orderCount = 0;
bool visitedGlobal[MAX];            




int addLocation(string name) {
    if (V >= MAX) return -1;        
    names[V] = name;
    degree[V] = 0;
    for (int i = 0; i < MAX; i++) { 
        adjMatrix[V][i] = 0;
        adjMatrix[i][V] = 0;
    }
    V++;
    return V - 1;                   
}

bool addPath(int a, int b) {
    if (a < 0 || b < 0 || a >= V || b >= V) return false;
    if (a == b) return false;                 
    if (adjMatrix[a][b] == 1) return false;   

    adjList[a][degree[a]] = b;  degree[a]++;  
    adjList[b][degree[b]] = a;  degree[b]++;  
    adjMatrix[a][b] = 1;
    adjMatrix[b][a] = 1;
    return true;
}


string toLowerCase(string s) {
    for (int i = 0; i < (int)s.length(); i++)
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] + 32;
    return s;
}


int findLocation(string name) {
    name = toLowerCase(name);
    for (int i = 0; i < V; i++)
        if (toLowerCase(names[i]) == name) return i;
    return -1;
}




void showLocations() {
    cout << "\nCampus Locations:\n";
    for (int i = 0; i < V; i++)
        cout << "  " << i << ". " << names[i] << endl;
}

void showAdjacencyList() {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < V; i++) {
        cout << "  " << names[i] << " -> ";
        for (int j = 0; j < degree[i]; j++) {
            cout << names[adjList[i][j]];
            if (j < degree[i] - 1) cout << ", ";
        }
        cout << endl;
    }
}

void showAdjacencyMatrix() {
    cout << "\nAdjacency Matrix:\n     ";
    for (int i = 0; i < V; i++) cout << i << " ";
    cout << endl;
    for (int i = 0; i < V; i++) {
        cout << "  " << i << " |";
        for (int j = 0; j < V; j++) cout << " " << adjMatrix[i][j];
        cout << "   (" << names[i] << ")" << endl;
    }
}


void printNames(int arr[], int n, string sep) {
    for (int i = 0; i < n; i++) {
        cout << names[arr[i]];
        if (i < n - 1) cout << sep;
    }
    cout << endl;
}


string namesToString(int arr[], int n, string sep) {
    string result = "";
    for (int i = 0; i < n; i++) {
        result = result + names[arr[i]];
        if (i < n - 1) result = result + sep;
    }
    return result;
}






int bfsShortestPath(int src, int dest, int path[]) {
    bool visited[MAX];
    int parent[MAX];            
    int queue[MAX];             
    int front = 0, rear = 0;

    for (int i = 0; i < V; i++) { visited[i] = false; parent[i] = -1; }

    visited[src] = true;
    queue[rear] = src; rear++;              

    while (front < rear) {
        int u = queue[front]; front++;      
        if (u == dest) break;               

        for (int i = 0; i < degree[u]; i++) {
            int v = adjList[u][i];
            if (visited[v] == false) {
                visited[v] = true;
                parent[v] = u;              
                queue[rear] = v; rear++;    
            }
        }
    }

    if (visited[dest] == false) return 0;   

    
    int temp[MAX];
    int len = 0;
    int at = dest;
    while (at != -1) {
        temp[len] = at; len++;
        at = parent[at];
    }
    
    for (int i = 0; i < len; i++) path[i] = temp[len - 1 - i];
    return len;
}


void bfsTraversal(int src) {
    bool visited[MAX];
    int queue[MAX];
    int front = 0, rear = 0;
    for (int i = 0; i < V; i++) visited[i] = false;
    orderCount = 0;

    visited[src] = true;
    queue[rear] = src; rear++;
    while (front < rear) {
        int u = queue[front]; front++;
        order[orderCount] = u; orderCount++;
        for (int i = 0; i < degree[u]; i++) {
            int v = adjList[u][i];
            if (visited[v] == false) {
                visited[v] = true;
                queue[rear] = v; rear++;
            }
        }
    }
}




void dfsHelper(int u) {
    visitedGlobal[u] = true;
    order[orderCount] = u; orderCount++;
    for (int i = 0; i < degree[u]; i++) {
        int v = adjList[u][i];
        if (visitedGlobal[v] == false) dfsHelper(v);
    }
}

void dfsRecursive(int src) {
    for (int i = 0; i < V; i++) visitedGlobal[i] = false;
    orderCount = 0;
    dfsHelper(src);
}




void dfsIterative(int src) {
    bool visited[MAX];
    int stack[MAX * MAX];       
    int top = -1;
    for (int i = 0; i < V; i++) visited[i] = false;
    orderCount = 0;

    top++; stack[top] = src;                
    while (top >= 0) {
        int u = stack[top]; top--;          
        if (visited[u] == true) continue;
        visited[u] = true;
        order[orderCount] = u; orderCount++;
        
        for (int i = degree[u] - 1; i >= 0; i--) {
            int v = adjList[u][i];
            if (visited[v] == false) { top++; stack[top] = v; }
        }
    }
}


bool isReachable(int src, int dest) {
    dfsRecursive(src);
    return visitedGlobal[dest];
}




void showComponents() {
    bool seen[MAX];
    for (int i = 0; i < V; i++) seen[i] = false;

    int componentNo = 0;
    for (int start = 0; start < V; start++) {
        if (seen[start] == false) {
            dfsRecursive(start);            
            componentNo++;
            cout << "  Component " << componentNo << ": ";
            printNames(order, orderCount, ", ");
            for (int i = 0; i < orderCount; i++) seen[order[i]] = true;
        }
    }
    cout << "Total connected components: " << componentNo << endl;
}




int testsPassed = 0;
int testsTotal = 0;

void runTest(string description, string from, string to, string expected) {
    int path[MAX];
    int s = findLocation(from);
    int d = findLocation(to);
    int len = bfsShortestPath(s, d, path);

    string actual;
    if (len == 0) actual = "No route";
    else actual = namesToString(path, len, " -> ");

    testsTotal++;
    cout << "Test " << testsTotal << ": " << description << endl;
    cout << "  Input    : " << from << " to " << to << endl;
    cout << "  Expected : " << expected << endl;
    cout << "  Actual   : " << actual << endl;
    if (actual == expected) { cout << "  Result   : PASS" << endl << endl; testsPassed++; }
    else                      cout << "  Result   : FAIL" << endl << endl;
}

void runAllTests() {
    testsPassed = 0;
    testsTotal = 0;
    cout << "\n================ TEST CASES ================\n";
    runTest("Direct route",            "Main Gate", "Library", "Main Gate -> Library");
    runTest("Multi-stop route",        "Main Gate", "Lab",     "Main Gate -> Library -> Block 1 -> Lab");
    runTest("Unreachable destination", "Main Gate", "Hostel",  "No route");
    runTest("Same source and destination", "Cafeteria", "Cafeteria", "Cafeteria");
    runTest("Route inside separate island", "Hostel", "Sports Ground", "Hostel -> Sports Ground");
    cout << "Summary: " << testsPassed << "/" << testsTotal << " tests passed." << endl;
}




void buildSampleCampus() {
    int gate   = addLocation("Main Gate");      
    int lib    = addLocation("Library");        
    int b1     = addLocation("Block 1");        
    int b2     = addLocation("Block 2");        
    int cafe   = addLocation("Cafeteria");      
    int aud    = addLocation("Auditorium");     
    int park   = addLocation("Parking");        
    int lab    = addLocation("Lab");            
    int hostel = addLocation("Hostel");         
    int sports = addLocation("Sports Ground");  

    addPath(gate, lib);
    addPath(gate, park);
    addPath(lib, b1);
    addPath(lib, cafe);
    addPath(b1, b2);
    addPath(b1, lab);
    addPath(cafe, aud);
    addPath(b2, aud);
    addPath(park, cafe);
    addPath(lab, b2);
    addPath(hostel, sports);
}




bool isNumber(string s) {
    if (s.length() == 0) return false;
    for (int i = 0; i < (int)s.length(); i++)
        if (s[i] < '0' || s[i] > '9') return false;
    return true;
}


int readLocation(string prompt) {
    string s;
    cout << prompt << " (name or id): ";
    getline(cin, s);
    if (isNumber(s)) {
        int id = atoi(s.c_str());
        if (id < V) return id;
        return -1;
    }
    return findLocation(s);
}

void showMenu() {
    cout << "\n=========== CAMPUS ROUTE FINDER ===========\n";
    cout << " 1. Show all locations\n";
    cout << " 2. Show adjacency list\n";
    cout << " 3. Show adjacency matrix\n";
    cout << " 4. Find shortest route (BFS)\n";
    cout << " 5. DFS traversal from a location\n";
    cout << " 6. Check if destination is reachable (DFS)\n";
    cout << " 7. Show reachable / unreachable locations\n";
    cout << " 8. Show connected components\n";
    cout << " 9. Add a new location\n";
    cout << "10. Add a new path\n";
    cout << "11. Run test cases\n";
    cout << "12. Complexity notes\n";
    cout << " 0. Exit\n";
    cout << "Enter choice: ";
}

void showComplexity() {
    cout << "\n--- Complexity (V = locations, E = paths) ---\n";
    cout << "BFS / DFS with adjacency list  : Time O(V + E), Space O(V)\n";
    cout << "BFS / DFS with adjacency matrix: Time O(V*V),   Space O(V)\n";
    cout << "Storage: list = O(V + E), matrix = O(V*V)\n";
    cout << "Checking one edge: list = O(neighbours), matrix = O(1)\n";
    cout << "A campus map is sparse (few paths per place), so the list is better.\n";
}





void saveCampus() {
    ofstream out("campus_data.txt");
    if (!out) {
        cout << "Could not save campus data.\n";
        return;
    }
    out << V << endl;
    for (int i = 0; i < V; i++) out << names[i] << endl;
    int edges = 0;
    for (int i = 0; i < V; i++)
        for (int j = i + 1; j < V; j++)
            if (adjMatrix[i][j]) edges++;
    out << edges << endl;
    for (int i = 0; i < V; i++)
        for (int j = i + 1; j < V; j++)
            if (adjMatrix[i][j]) out << i << " " << j << endl;
}

bool loadCampus() {
    ifstream in("campus_data.txt");
    if (!in) return false;
    int count;
    if (!(in >> count) || count < 0 || count > MAX) return false;
    in.ignore(10000, '\n');
    string loadedNames[MAX];
    for (int i = 0; i < count; i++)
        if (!getline(in, loadedNames[i])) return false;
    int edges;
    if (!(in >> edges) || edges < 0 || edges > MAX * MAX) return false;
    V = 0;
    for (int i = 0; i < MAX; i++) {
        degree[i] = 0;
        for (int j = 0; j < MAX; j++) adjMatrix[i][j] = 0;
    }
    for (int i = 0; i < count; i++) addLocation(loadedNames[i]);
    for (int i = 0; i < edges; i++) {
        int a, b;
        if (!(in >> a >> b) || !addPath(a, b)) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    buildSampleCampus();
    if (loadCampus()) cout << "Campus data loaded from campus_data.txt.\n";

    
    if (argc > 1 && string(argv[1]) == "--test") {
        runAllTests();
        return 0;
    }

    int choice = -1;
    string line;
    while (choice != 0) {
        showMenu();
        getline(cin, line);
        choice = atoi(line.c_str());

        if (choice == 1) {
            showLocations();
        }
        else if (choice == 2) {
            showAdjacencyList();
        }
        else if (choice == 3) {
            showAdjacencyMatrix();
        }
        else if (choice == 4) {
            showLocations();
            int s = readLocation("Source");
            int d = readLocation("Destination");
            if (s < 0 || d < 0) { cout << "Invalid location.\n"; continue; }
            int path[MAX];
            int len = bfsShortestPath(s, d, path);
            if (len == 0) cout << "No route exists from " << names[s] << " to " << names[d] << ".\n";
            else {
                cout << "Shortest route (" << len - 1 << " step(s)): ";
                printNames(path, len, " -> ");
            }
        }
        else if (choice == 5) {
            int s = readLocation("Start location");
            if (s < 0) { cout << "Invalid location.\n"; continue; }
            dfsRecursive(s);
            cout << "DFS (recursive): ";  printNames(order, orderCount, ", ");
            dfsIterative(s);
            cout << "DFS (using stack): "; printNames(order, orderCount, ", ");
            bfsTraversal(s);
            cout << "BFS (for comparison): "; printNames(order, orderCount, ", ");
        }
        else if (choice == 6) {
            int s = readLocation("Source");
            int d = readLocation("Destination");
            if (s < 0 || d < 0) { cout << "Invalid location.\n"; continue; }
            if (isReachable(s, d)) cout << names[d] << " IS reachable from " << names[s] << ".\n";
            else                   cout << names[d] << " is NOT reachable from " << names[s] << ".\n";
        }
        else if (choice == 7) {
            int s = readLocation("Start location");
            if (s < 0) { cout << "Invalid location.\n"; continue; }
            dfsRecursive(s);
            cout << "Reachable    : "; printNames(order, orderCount, ", ");
            int notReached[MAX];
            int count = 0;
            for (int i = 0; i < V; i++)
                if (visitedGlobal[i] == false) { notReached[count] = i; count++; }
            if (count == 0) cout << "Disconnected : none\n";
            else { cout << "Disconnected : "; printNames(notReached, count, ", "); }
        }
        else if (choice == 8) {
            showComponents();
        }
        else if (choice == 9) {
            string n;
            cout << "New location name: ";
            getline(cin, n);
            if (n == "" || findLocation(n) != -1) cout << "Empty or duplicate name.\n";
            else {
                int id = addLocation(n);
                if (id == -1) cout << "Graph is full (max " << MAX << " locations).\n";
                else { cout << "Added '" << n << "' with id " << id << ".\n"; saveCampus(); }
            }
        }
        else if (choice == 10) {
            int a = readLocation("First location");
            int b = readLocation("Second location");
            if (addPath(a, b)) { cout << "Path added.\n"; saveCampus(); }
            else cout << "Could not add path (invalid, same, or already exists).\n";
        }
        else if (choice == 11) {
            runAllTests();
        }
        else if (choice == 12) {
            showComplexity();
        }
        else if (choice == 0) {
            saveCampus();
            cout << "Goodbye!\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
