
#include <iostream>
#include <iomanip>      
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>      
using namespace std;


struct Student {
    int id;                 
    string name;
    string department;
};

struct Node {
    Student data;
    Node* left;
    Node* right;
};


int comparisons = 0;        
bool inserted = false;      
bool deleted = false;       
string caseType = "";       
string outText = "";        


string intToString(int n) {
    if (n == 0) return "0";
    string s = "";
    while (n > 0) {
        s = char('0' + n % 10) + s;
        n = n / 10;
    }
    return s;
}


Student makeStudent(int id, string name, string dept) {
    Student s;
    s.id = id;
    s.name = name;
    s.department = dept;
    return s;
}


Node* createNode(Student s) {
    Node* n = new Node;
    n->data = s;
    n->left = NULL;
    n->right = NULL;
    return n;
}




Node* insertNode(Node* node, Student s) {
    if (node == NULL) {                 
        inserted = true;
        return createNode(s);
    }
    comparisons++;
    if (s.id < node->data.id)
        node->left = insertNode(node->left, s);
    else if (s.id > node->data.id)
        node->right = insertNode(node->right, s);
    else
        inserted = false;               
    return node;
}




Node* searchNode(Node* node, int id) {
    if (node == NULL) return NULL;
    comparisons++;
    if (id == node->data.id) return node;
    if (id < node->data.id) return searchNode(node->left, id);
    return searchNode(node->right, id);
}


Node* findMin(Node* node) {
    while (node->left != NULL) node = node->left;
    return node;
}







Node* deleteNode(Node* node, int id) {
    if (node == NULL) return NULL;      
    comparisons++;

    if (id < node->data.id) {
        node->left = deleteNode(node->left, id);
    }
    else if (id > node->data.id) {
        node->right = deleteNode(node->right, id);
    }
    else {                              
        deleted = true;

        if (node->left == NULL && node->right == NULL) {        
            caseType = "leaf node";
            delete node;
            return NULL;
        }
        else if (node->left == NULL) {                          
            caseType = "node with one child (right)";
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL) {                         
            caseType = "node with one child (left)";
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else {                                                  
            Node* successor = findMin(node->right);  
            node->data = successor->data;            
            node->right = deleteNode(node->right, successor->data.id);  
            caseType = "node with two children";     
        }
    }
    return node;
}




void printStudentRow(Student s) {
    cout << "  " << left << setw(8) << s.id << setw(22) << s.name << s.department << endl;
}

void printHeader() {
    cout << "  ID      Name                  Department" << endl;
    cout << "  ------  --------------------  ----------------------" << endl;
}


void printInorder(Node* node) {
    if (node == NULL) return;
    printInorder(node->left);
    printStudentRow(node->data);
    printInorder(node->right);
}


void inorderIds(Node* node) {
    if (node == NULL) return;
    inorderIds(node->left);
    outText = outText + intToString(node->data.id) + " ";
    inorderIds(node->right);
}
void preorderIds(Node* node) {
    if (node == NULL) return;
    outText = outText + intToString(node->data.id) + " ";
    preorderIds(node->left);
    preorderIds(node->right);
}
void postorderIds(Node* node) {
    if (node == NULL) return;
    postorderIds(node->left);
    postorderIds(node->right);
    outText = outText + intToString(node->data.id) + " ";
}


string getInorder(Node* root)   { outText = ""; inorderIds(root);   return outText; }
string getPreorder(Node* root)  { outText = ""; preorderIds(root);  return outText; }
string getPostorder(Node* root) { outText = ""; postorderIds(root); return outText; }




int height(Node* node) {                
    if (node == NULL) return 0;
    int lh = height(node->left);
    int rh = height(node->right);
    if (lh > rh) return lh + 1;
    return rh + 1;
}

int countNodes(Node* node) {
    if (node == NULL) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}


void printTree(Node* node, int level) {
    if (node == NULL) return;
    printTree(node->right, level + 1);
    for (int i = 0; i < level; i++) cout << "      ";
    cout << node->data.id << endl;
    printTree(node->left, level + 1);
}


void freeTree(Node* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}




const int SAMPLE_COUNT = 12;
Student samples[SAMPLE_COUNT] = {
    {1050, "Aarav Sharma",   "Computer Science"},
    {1030, "Priya Verma",    "Information Technology"},
    {1070, "Rohan Gupta",    "Electronics"},
    {1020, "Simran Kaur",    "Computer Science"},
    {1040, "Karan Mehta",    "Mechanical"},
    {1060, "Neha Singh",     "Civil"},
    {1080, "Arjun Malhotra", "Computer Science"},
    {1010, "Ishita Jain",    "Information Technology"},
    {1035, "Harpreet Singh", "Electronics"},
    {1065, "Meera Nair",     "Mechanical"},
    {1075, "Vikram Rao",     "Civil"},
    {1090, "Anjali Das",     "Computer Science"}
};




void runOrder(string label, int ids[], int n) {
    Node* root = NULL;
    comparisons = 0;
    for (int i = 0; i < n; i++)
        root = insertNode(root, makeStudent(ids[i], "Student", "Dept"));
    int insertComparisons = comparisons;

    comparisons = 0;
    for (int i = 0; i < n; i++) searchNode(root, ids[i]);   
    int searchComparisons = comparisons;

    cout << "  " << label << endl;
    cout << "    Height of tree             : " << height(root) << endl;
    cout << "    Comparisons for all inserts: " << insertComparisons << endl;
    cout << "    Comparisons for " << n << " searches: " << searchComparisons
         << "  (average " << (double)searchComparisons / n << " per search)" << endl;
    freeTree(root);
}

void efficiencyExperiment() {
    const int N = 15;
    int balanced[N] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
    int sorted[N];
    for (int i = 0; i < N; i++) sorted[i] = i + 1;

    cout << "\n===== EFFICIENCY EXPERIMENT (N = 15) =====\n";
    runOrder("A) Balanced-looking order (8,4,12,2,6,...)", balanced, N);
    runOrder("B) Sorted order (1,2,3,...,15)", sorted, N);
    cout << "\nSorted insertion makes every node a right child, so the tree becomes\n";
    cout << "a chain (like a linked list) of height N, and search becomes O(N).\n";
    cout << "A balanced-looking order keeps the height near log2(N+1).\n";
}




int testsPassed = 0;
int testsTotal = 0;

void check(string name, string expected, string actual) {
    testsTotal++;
    cout << "Test " << testsTotal << ": " << name << endl;
    cout << "  Expected: " << expected << endl;
    cout << "  Actual  : " << actual << endl;
    if (expected == actual) { cout << "  Result  : PASS" << endl << endl; testsPassed++; }
    else                      cout << "  Result  : FAIL" << endl << endl;
}






Node* buildTestTree() {
    int ids[8] = {50, 30, 70, 20, 40, 60, 80, 10};
    Node* root = NULL;
    for (int i = 0; i < 8; i++)
        root = insertNode(root, makeStudent(ids[i], "S" + intToString(ids[i]), "CSE"));
    return root;
}

void runAllTests() {
    testsPassed = 0;
    testsTotal = 0;
    cout << "\n================ TEST CASES ================\n";
    Node* root;

    root = buildTestTree();
    check("Inorder traversal is sorted", "10 20 30 40 50 60 70 80 ", getInorder(root));
    check("Preorder traversal",          "50 30 20 10 40 70 60 80 ", getPreorder(root));
    check("Postorder traversal",         "10 20 40 30 60 80 70 50 ", getPostorder(root));

    inserted = true;
    root = insertNode(root, makeStudent(40, "Duplicate", "CSE"));
    string dupResult = inserted ? "accepted" : "rejected";
    check("Duplicate ID 40 is rejected", "rejected, size=8", dupResult + ", size=" + intToString(countNodes(root)));

    check("Search existing ID 60", "found",     searchNode(root, 60) != NULL ? "found" : "not found");
    check("Search missing ID 65",  "not found", searchNode(root, 65) != NULL ? "found" : "not found");
    freeTree(root);

    root = buildTestTree();
    deleted = false;
    root = deleteNode(root, 10);
    check("Delete LEAF node (10)", "leaf node | 20 30 40 50 60 70 80 ", caseType + " | " + getInorder(root));
    freeTree(root);

    root = buildTestTree();
    root = deleteNode(root, 20);
    check("Delete node with ONE child (20)", "node with one child (left) | 10 30 40 50 60 70 80 ",
          caseType + " | " + getInorder(root));
    freeTree(root);

    root = buildTestTree();
    root = deleteNode(root, 30);
    check("Delete node with TWO children (30)", "node with two children | 10 20 40 50 60 70 80 ",
          caseType + " | " + getInorder(root));
    check("Preorder after two-child delete", "50 40 20 10 70 60 80 ", getPreorder(root));
    freeTree(root);

    root = buildTestTree();
    deleted = false;
    root = deleteNode(root, 99);
    string delResult = deleted ? "deleted" : "not deleted";
    check("Delete non-existent ID 99", "not deleted, size=8", delResult + ", size=" + intToString(countNodes(root)));
    freeTree(root);

    cout << "Summary: " << testsPassed << "/" << testsTotal << " tests passed." << endl;
}




bool isNumber(string s) {
    if (s.length() == 0) return false;
    for (int i = 0; i < (int)s.length(); i++)
        if (s[i] < '0' || s[i] > '9') return false;
    return true;
}

int readInt(string prompt) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        if (isNumber(line)) return atoi(line.c_str());
        cout << "  Please enter a valid positive number.\n";
    }
}

void showMenu() {
    cout << "\n======= STUDENT RECORD SEARCH SYSTEM (BST) =======\n";
    cout << " 1. Insert a student\n";
    cout << " 2. Search by enrolment ID\n";
    cout << " 3. Delete by enrolment ID\n";
    cout << " 4. Display sorted records (Inorder)\n";
    cout << " 5. Preorder traversal\n";
    cout << " 6. Postorder traversal\n";
    cout << " 7. Load 12 sample records\n";
    cout << " 8. Show tree shape, height and size\n";
    cout << " 9. Efficiency experiment (balanced vs sorted insertion)\n";
    cout << "10. Run test cases\n";
    cout << "11. Complexity notes\n";
    cout << " 0. Exit\n";
    cout << "Enter choice: ";
}

void showComplexity() {
    cout << "\n--- Complexity (n = records, h = height of tree) ---\n";
    cout << "Insert / Search / Delete : O(h) -> average O(log n), worst case O(n)\n";
    cout << "Traversals               : O(n) time\n";
    cout << "Space for n records      : O(n)\n\n";
    cout << "Why O(n) in the worst case?\n";
    cout << "If IDs are inserted in sorted order (1,2,3,...) every new node becomes\n";
    cout << "the right child of the previous one, so the tree is just a chain of height n.\n\n";
    cout << "How an AVL tree helps:\n";
    cout << "An AVL tree checks the balance factor (left height - right height) of every\n";
    cout << "node. If it goes beyond -1 or +1, rotations (LL, RR, LR, RL) fix the shape.\n";
    cout << "So the height always stays about log n and every operation stays O(log n).\n";
}


void writeRecords(Node* node, ofstream& out) {
    if (node == NULL) return;
    writeRecords(node->left, out);
    out << node->data.id << "|" << node->data.name << "|" << node->data.department << endl;
    writeRecords(node->right, out);
}

void saveRecords(Node* root) {
    ofstream out("students_data.txt");
    if (!out) {
        cout << "Could not save student records.\n";
        return;
    }
    writeRecords(root, out);
}

bool loadRecords(Node*& root) {
    ifstream in("students_data.txt");
    if (!in) return false;
    freeTree(root);
    root = NULL;
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string idText, name, department;
        if (!getline(ss, idText, '|') || !getline(ss, name, '|') || !getline(ss, department)) continue;
        int id = atoi(idText.c_str());
        if (id > 0 && name != "") {
            inserted = false;
            root = insertNode(root, makeStudent(id, name, department));
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    
    if (argc > 1 && string(argv[1]) == "--test") {
        runAllTests();
        efficiencyExperiment();
        return 0;
    }

    Node* root = NULL;
    for (int i = 0; i < SAMPLE_COUNT; i++) root = insertNode(root, samples[i]);
    if (loadRecords(root)) cout << "Student records loaded from students_data.txt.\n";
    else cout << "(12 sample records pre-loaded)\n";

    int choice = -1;
    string line;
    while (choice != 0) {
        showMenu();
        getline(cin, line);
        choice = atoi(line.c_str());

        if (choice == 1) {
            Student s;
            s.id = readInt("Enrolment ID: ");
            cout << "Name: ";        getline(cin, s.name);
            cout << "Department: ";  getline(cin, s.department);
            if (s.id == 0 || s.name == "") {
                cout << "Invalid input (ID must be positive and name is required).\n";
            } else {
                inserted = false;
                root = insertNode(root, s);
                if (inserted) { cout << "Inserted successfully.\n"; saveRecords(root); }
                else cout << "Error: enrolment ID " << s.id << " already exists. Duplicate rejected.\n";
            }
        }
        else if (choice == 2) {
            int id = readInt("Enrolment ID to search: ");
            comparisons = 0;
            Node* found = searchNode(root, id);
            if (found != NULL) {
                cout << "Record found:\n";
                printHeader();
                printStudentRow(found->data);
            } else {
                cout << "No student found with ID " << id << ".\n";
            }
            cout << "(comparisons made: " << comparisons << ")\n";
        }
        else if (choice == 3) {
            int id = readInt("Enrolment ID to delete: ");
            deleted = false;
            caseType = "";
            root = deleteNode(root, id);
            if (deleted) { cout << "Deleted ID " << id << " (" << caseType << ").\n"; saveRecords(root); }
            else cout << "No student found with ID " << id << ". Nothing deleted.\n";
        }
        else if (choice == 4) {
            cout << "\nRecords in sorted order (Inorder) - " << countNodes(root) << " records\n";
            if (root == NULL) cout << "  (no records)\n";
            else { printHeader(); printInorder(root); }
        }
        else if (choice == 5) {
            cout << "Preorder  (Root, Left, Right): " << getPreorder(root) << endl;
        }
        else if (choice == 6) {
            cout << "Postorder (Left, Right, Root): " << getPostorder(root) << endl;
        }
        else if (choice == 7) {
            int added = 0;
            for (int i = 0; i < SAMPLE_COUNT; i++) {
                inserted = false;
                root = insertNode(root, samples[i]);
                if (inserted) added++;
            }
            cout << added << " sample record(s) added (duplicates skipped).\n";
            saveRecords(root);
        }
        else if (choice == 8) {
            if (root == NULL) cout << "(empty tree)\n";
            else {
                cout << "Tree shape (turn your head left: root is at the left edge):\n";
                printTree(root, 0);
            }
            cout << "Size: " << countNodes(root) << "   Height: " << height(root) << endl;
        }
        else if (choice == 9) {
            efficiencyExperiment();
        }
        else if (choice == 10) {
            runAllTests();
        }
        else if (choice == 11) {
            showComplexity();
        }
        else if (choice == 0) {
            saveRecords(root);
            cout << "Goodbye!\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    freeTree(root);
    return 0;
}
