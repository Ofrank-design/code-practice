/*
 * ╔══════════════════════════════════════════════════════════════╗
 * ║         GHANA PROCUREMENT ENGINE — C++                      ║
 * ║         Frank Oduro · KSTU BSc Procurement & SCM            ║
 * ║         Route Optimizer · Inventory · Sorting · 7 Projects  ║
 * ╚══════════════════════════════════════════════════════════════╝
 *
 * Covers:
 * → Logistics Route Optimizer (Dijkstra's algorithm — Ghana cities)
 * → Inventory Management System (structs + vectors)
 * → Supplier Sorting Engine (multiple algorithms compared)
 * → Links to all 7 portfolio projects
 *
 * Compile: g++ -o procurement procurement.cpp -std=c++17
 * Run:     ./procurement
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
#include <iomanip>
#include <cmath>
#include <climits>
#include <chrono>

using namespace std;

// ── ANSI COLORS ──────────────────────────────────────────
const string GOLD   = "\033[33m";
const string GREEN  = "\033[32m";
const string CYAN   = "\033[36m";
const string RED    = "\033[31m";
const string PURPLE = "\033[35m";
const string BOLD   = "\033[1m";
const string DIM    = "\033[2m";
const string RESET  = "\033[0m";

// ══════════════════════════════════════════════════════════
//  DATA STRUCTURES
// ══════════════════════════════════════════════════════════

struct Supplier {
    int    id;
    string name;
    string category;
    double delivery;   // score /10
    double quality;    // score /10
    double financial;  // score /10
    double compliance; // score /10
    double annualSpend;

    double weightedScore() const {
        return (delivery * 0.30) + (quality * 0.30) +
               (financial * 0.20) + (compliance * 0.20);
    }

    string riskLevel() const {
        double s = weightedScore();
        if (s >= 7.0) return GREEN + "LOW"    + RESET;
        if (s >= 4.0) return GOLD  + "MEDIUM" + RESET;
        return RED + "HIGH" + RESET;
    }
};

struct InventoryItem {
    string name;
    int    stock;
    double unitPrice;
    double annualDemand;
    double orderCost;
    double holdCost;
    string abcClass;

    double eoq() const {
        return sqrt((2.0 * annualDemand * orderCost) / holdCost);
    }

    double annualValue() const {
        return annualDemand * unitPrice;
    }

    double reorderPoint() const {
        double dailyDemand = annualDemand / 365.0;
        double safetyStock = dailyDemand * 7;
        return (dailyDemand * 14) + safetyStock;
    }
};

struct City {
    string name;
    string region;
};

struct Route {
    int    from;
    int    to;
    double distKm;
    double costPerKg; // GHS per kg per km
};

struct PurchaseOrder {
    string poNumber;
    string supplier;
    string item;
    int    quantity;
    double unitPrice;
    string status;

    double totalValue() const { return quantity * unitPrice; }
};

// ══════════════════════════════════════════════════════════
//  SEED DATA
// ══════════════════════════════════════════════════════════

vector<Supplier> suppliers = {
    {1, "Accra Supplies Ltd",    "Medical",     8.0, 7.0, 6.0, 9.0, 320000},
    {2, "Kumasi Tech Hub",       "IT",          5.0, 6.0, 4.0, 7.0, 210000},
    {3, "Tema Port Logistics",   "Logistics",   3.0, 4.0, 3.0, 5.0, 180000},
    {4, "KSTU Medical Stores",   "Medical",     9.0, 8.0, 7.0, 9.0, 150000},
    {5, "Ashanti Office Hub",    "Office",      7.0, 8.0, 6.0, 8.0,  95000},
    {6, "Greater Accra Maint.",  "Maintenance", 4.0, 5.0, 4.0, 6.0, 140000},
    {7, "Takoradi Freight Co.",  "Logistics",   6.0, 5.0, 5.0, 7.0, 160000},
    {8, "Northern Supply Chain", "Medical",     5.0, 6.0, 5.0, 8.0,  90000},
};

vector<InventoryItem> inventory = {
    {"Surgical Gloves",  500, 12.50, 2400, 60.0, 2.50, "A"},
    {"Hand Sanitizer",   150, 15.00,  800, 35.0, 3.00, "A"},
    {"A4 Paper",         200,  8.00, 1200, 40.0, 1.50, "B"},
    {"Printer Toner",     50, 85.00,  300, 50.0, 8.00, "B"},
    {"Biro Pens",        300,  3.50,  600, 20.0, 0.75, "C"},
    {"Latex Gloves",     400, 10.00, 1800, 55.0, 2.00, "A"},
    {"Disinfectant",     120, 18.00,  960, 45.0, 3.50, "B"},
    {"Face Masks",      1200,  5.00, 3600, 40.0, 1.00, "A"},
};

// Ghana cities (0=Accra, 1=Kumasi, 2=Tema, 3=Takoradi, 4=Tamale, 5=Cape Coast)
vector<City> cities = {
    {"Accra",      "Greater Accra"},
    {"Kumasi",     "Ashanti"},
    {"Tema",       "Greater Accra"},
    {"Takoradi",   "Western"},
    {"Tamale",     "Northern"},
    {"Cape Coast", "Central"},
};

// Road distances in km between Ghana cities
vector<vector<double>> distances = {
//  Accra  Kumasi  Tema  Takoradi  Tamale  CapeCo
    {0,    248,    25,   224,      598,    165},  // Accra
    {248,  0,      265,  270,      385,    167},  // Kumasi
    {25,   265,    0,    241,      615,    182},  // Tema
    {224,  270,    241,  0,        633,    136},  // Takoradi
    {598,  385,    615,  633,      0,      521},  // Tamale
    {165,  167,    182,  136,      521,    0  },  // Cape Coast
};

vector<PurchaseOrder> orders = {
    {"PO-2026-001", "Accra Supplies Ltd",  "Surgical Gloves",  500, 12.50, "APPROVED"},
    {"PO-2026-002", "Kumasi Tech Hub",     "Laptop Computer",    5, 3500,  "PENDING"},
    {"PO-2026-003", "Ashanti Office Hub",  "A4 Paper",         200,  8.00, "DELIVERED"},
    {"PO-2026-004", "Tema Port Logistics", "Freight Services",   1, 45000, "APPROVED"},
};

// ══════════════════════════════════════════════════════════
//  HELPERS
// ══════════════════════════════════════════════════════════

string ghs(double amount) {
    ostringstream ss;
    ss << "GHS " << fixed << setprecision(2) << amount;
    return ss.str();
}

void sectionHeader(const string& title, const string& subtitle) {
    cout << GOLD << BOLD << "\n  ╔══════════════════════════════════════════════╗\n";
    cout << "  ║  " << left << setw(44) << title << "║\n";
    cout << "  ╚══════════════════════════════════════════════╝\n" << RESET;
    cout << DIM << "  " << subtitle << "\n" << RESET;
}

void printLine(int len = 60) {
    cout << DIM << "  " << string(len, '─') << RESET << "\n";
}

// ══════════════════════════════════════════════════════════
//  1. LOGISTICS ROUTE OPTIMIZER — Dijkstra's Algorithm
// ══════════════════════════════════════════════════════════

vector<double> dijkstra(int src, int n) {
    vector<double> dist(n, INT_MAX);
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (int v = 0; v < n; v++) {
            if (distances[u][v] > 0) {
                double newDist = dist[u] + distances[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    pq.push({newDist, v});
                }
            }
        }
    }
    return dist;
}

void routeOptimizer() {
    sectionHeader("🚚 LOGISTICS ROUTE OPTIMIZER", "Project 8 — Dijkstra's Shortest Path · Ghana Cities");

    cout << "\n  Ghana City Network:\n";
    for (int i = 0; i < (int)cities.size(); i++) {
        cout << "  [" << i << "] " << cities[i].name << " (" << cities[i].region << ")\n";
    }

    cout << "\n  Shortest Routes FROM ACCRA (Dijkstra's Algorithm):\n";
    printLine();
    cout << BOLD << setw(20) << left << "  Destination"
         << setw(12) << "Distance"
         << setw(16) << "Freight Cost"
         << "Est. Time\n" << RESET;
    printLine();

    vector<double> shortestDist = dijkstra(0, cities.size());
    double ratePerKgKm = 0.08; // GHS per kg per km (road)
    double avgLoad     = 500;  // kg

    for (int i = 1; i < (int)cities.size(); i++) {
        double dist     = shortestDist[i];
        double cost     = dist * ratePerKgKm * avgLoad;
        double hours    = dist / 80.0; // avg 80km/h
        cout << "  " << left << setw(18) << cities[i].name
             << setw(12) << (to_string((int)dist) + " km")
             << setw(16) << ghs(cost)
             << fixed << setprecision(1) << hours << " hrs\n";
    }

    cout << DIM << "\n  Rate: GHS 0.08/kg/km · Load: 500kg · Speed: 80km/h avg\n" << RESET;
    cout << DIM << "  Algorithm: Dijkstra's O((V+E) log V)\n" << RESET;
}

// ══════════════════════════════════════════════════════════
//  2. SUPPLIER SORTING ENGINE — Multiple Algorithms
// ══════════════════════════════════════════════════════════

// Bubble Sort — by score descending
vector<Supplier> bubbleSort(vector<Supplier> arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j].weightedScore() < arr[j+1].weightedScore())
                swap(arr[j], arr[j+1]);
    return arr;
}

// Selection Sort — by spend descending
vector<Supplier> selectionSort(vector<Supplier> arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int maxIdx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j].annualSpend > arr[maxIdx].annualSpend)
                maxIdx = j;
        swap(arr[i], arr[maxIdx]);
    }
    return arr;
}

// Merge Sort — by name alphabetically
void merge(vector<Supplier>& arr, int l, int m, int r) {
    vector<Supplier> left(arr.begin()+l, arr.begin()+m+1);
    vector<Supplier> right(arr.begin()+m+1, arr.begin()+r+1);
    int i=0, j=0, k=l;
    while (i<(int)left.size() && j<(int)right.size())
        arr[k++] = (left[i].name <= right[j].name) ? left[i++] : right[j++];
    while (i<(int)left.size()) arr[k++] = left[i++];
    while (j<(int)right.size()) arr[k++] = right[j++];
}

void mergeSort(vector<Supplier>& arr, int l, int r) {
    if (l < r) {
        int m = (l+r)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void sortingEngine() {
    sectionHeader("⚙️  SUPPLIER SORTING ENGINE", "Project 3 — Bubble · Selection · Merge Sort Compared");

    // Bubble sort by score
    cout << "\n  " << BOLD << "Bubble Sort — By Score (Descending):" << RESET << "\n";
    printLine();
    auto byScore = bubbleSort(suppliers);
    cout << BOLD << "  " << left << setw(25) << "Supplier" << setw(8) << "Score" << "Risk\n" << RESET;
    for (auto& s : byScore) {
        cout << "  " << setw(25) << s.name
             << setw(8) << fixed << setprecision(1) << s.weightedScore()
             << s.riskLevel() << "\n";
    }

    // Selection sort by spend
    cout << "\n  " << BOLD << "Selection Sort — By Annual Spend (Descending):" << RESET << "\n";
    printLine();
    auto bySpend = selectionSort(suppliers);
    cout << BOLD << "  " << left << setw(25) << "Supplier" << "Annual Spend\n" << RESET;
    for (auto& s : bySpend) {
        cout << "  " << setw(25) << s.name << ghs(s.annualSpend) << "\n";
    }

    // Merge sort alphabetically
    cout << "\n  " << BOLD << "Merge Sort — Alphabetical:" << RESET << "\n";
    printLine();
    auto alpha = suppliers;
    mergeSort(alpha, 0, alpha.size()-1);
    for (auto& s : alpha) cout << "  → " << s.name << "\n";

    // Algorithm comparison
    cout << "\n  " << BOLD << "Algorithm Complexity Comparison:\n" << RESET;
    printLine();
    cout << "  " << setw(18) << "Algorithm" << setw(12) << "Best" << setw(12) << "Average" << "Worst\n";
    cout << "  " << setw(18) << "Bubble Sort"    << setw(12) << "O(n)"    << setw(12) << "O(n²)"     << "O(n²)\n";
    cout << "  " << setw(18) << "Selection Sort" << setw(12) << "O(n²)"   << setw(12) << "O(n²)"     << "O(n²)\n";
    cout << "  " << setw(18) << "Merge Sort"     << setw(12) << "O(nlogn)"<< setw(12) << "O(n log n)"<< "O(n log n)\n";
}

// ══════════════════════════════════════════════════════════
//  3. INVENTORY MANAGEMENT — EOQ & ABC
// ══════════════════════════════════════════════════════════

void inventorySystem() {
    sectionHeader("📦 INVENTORY MANAGEMENT SYSTEM", "Project 4 — EOQ · ABC · Safety Stock · Fast C++ Structs");

    cout << "\n  " << BOLD << left
         << setw(18) << "Item"
         << setw(8)  << "EOQ"
         << setw(10) << "SafeStk"
         << setw(8)  << "ROP"
         << setw(14) << "Ann. Value"
         << "Class\n" << RESET;
    printLine(65);

    double totalValue = 0;
    for (auto& item : inventory) {
        double eoqVal = item.eoq();
        double rop    = item.reorderPoint();
        double ssafe  = (item.annualDemand / 365.0) * 7;
        double annVal = item.annualValue();
        totalValue   += annVal;

        string color = item.abcClass == "A" ? GOLD : item.abcClass == "B" ? CYAN : DIM;
        cout << "  " << left << setw(18) << item.name
             << setw(8)  << (int)eoqVal
             << setw(10) << (int)ssafe
             << setw(8)  << (int)rop
             << setw(14) << ghs(annVal)
             << color << item.abcClass << RESET << "\n";
    }

    printLine(65);
    cout << GOLD << BOLD << "  Total Inventory Value: " << ghs(totalValue) << RESET << "\n";

    // ABC summary
    int a=0, b=0, c=0;
    double aVal=0, bVal=0, cVal=0;
    for (auto& item : inventory) {
        if (item.abcClass=="A") { a++; aVal += item.annualValue(); }
        else if (item.abcClass=="B") { b++; bVal += item.annualValue(); }
        else { c++; cVal += item.annualValue(); }
    }
    cout << "\n  ABC Summary:\n";
    cout << GOLD   << "  A: " << a << " items · " << ghs(aVal) << " · Review weekly\n"   << RESET;
    cout << CYAN   << "  B: " << b << " items · " << ghs(bVal) << " · Review monthly\n"  << RESET;
    cout << DIM    << "  C: " << c << " items · " << ghs(cVal) << " · Review quarterly\n"<< RESET;
}

// ══════════════════════════════════════════════════════════
//  4. PORTFOLIO SUMMARY — All 7 Projects
// ══════════════════════════════════════════════════════════

void portfolioSummary() {
    sectionHeader("📋 PORTFOLIO SUMMARY", "Frank Oduro · 7 Projects · Acts 663 & 914");

    string projects[7][3] = {
        {"01", "SAP MM Procure-to-Pay Workflow",      "Year 2 · 2027"},
        {"02", "Mock SLA & Contract Negotiation",     "Year 2 · 2027"},
        {"03", "Supplier Scorecard & KPI Dashboard",  "Year 3 · 2028"},
        {"04", "Inventory Optimization Model",        "✅ Completed"},
        {"05", "Ghana Procurement Spend Dashboard",   "Year 3 · 2028"},
        {"06", "IT Category Management Plan",         "Year 4 · 2029"},
        {"07", "Tender Risk Assessment (Acts 663)",   "Year 3 · 2028"},
    };

    cout << "\n";
    for (auto& p : projects) {
        string color = p[2] == "✅ Completed" ? GREEN : GOLD;
        cout << "  " << BOLD << p[0] << RESET << "  "
             << left << setw(38) << p[1]
             << color << p[2] << RESET << "\n";
    }

    cout << "\n  " << BOLD << "C++ Features Used in This Project:\n" << RESET;
    cout << DIM;
    cout << "  → Structs with methods (OOP-lite)\n";
    cout << "  → STL vectors, maps, priority_queue\n";
    cout << "  → Dijkstra's shortest path algorithm\n";
    cout << "  → Bubble, Selection, Merge sort implementations\n";
    cout << "  → ANSI terminal colors and formatting\n";
    cout << "  → Chrono timing for algorithm comparison\n";
    cout << RESET;
    cout << "\n  " << DIM << "Portfolio: ofrank-design.github.io\n" << RESET;
    cout << "  " << DIM << "GitHub:    github.com/Ofrank-design\n" << RESET;
}

// ══════════════════════════════════════════════════════════
//  MAIN MENU
// ══════════════════════════════════════════════════════════

void printBanner() {
    cout << GOLD << BOLD;
    cout << "\n  ╔══════════════════════════════════════════════════════╗\n";
    cout <<   "  ║    GHANA PROCUREMENT ENGINE — C++  v1.0            ║\n";
    cout <<   "  ║    Frank Oduro · KSTU · Kumasi, Ghana 🇬🇭           ║\n";
    cout <<   "  ║    Route · Inventory · Sorting · 7 Projects         ║\n";
    cout <<   "  ╚══════════════════════════════════════════════════════╝\n";
    cout << RESET;
    cout << DIM << "  github.com/Ofrank-design · ofrank-design.github.io\n\n" << RESET;
}

int main() {
    printBanner();

    while (true) {
        cout << CYAN << BOLD << "\n  ══ MAIN MENU ══════════════════════════════\n" << RESET;
        cout << GOLD << "  [1]" << WHITE << " Route Optimizer     " << DIM << "→ Dijkstra's Algorithm\n" << RESET;
        cout << GOLD << "  [2]" << WHITE << " Supplier Sorter     " << DIM << "→ Bubble · Selection · Merge\n" << RESET;
        cout << GOLD << "  [3]" << WHITE << " Inventory System    " << DIM << "→ EOQ · ABC · Safety Stock\n" << RESET;
        cout << GOLD << "  [4]" << WHITE << " Portfolio Summary   " << DIM << "→ All 7 Projects\n" << RESET;
        cout << RED  << "  [0]" << WHITE << " Exit\n" << RESET;
        cout << CYAN << "  ════════════════════════════════════════════\n" << RESET;
        cout << GOLD << "  Select › " << RESET;

        string input;
        cin >> input;
        cin.ignore();

        if      (input == "1") routeOptimizer();
        else if (input == "2") sortingEngine();
        else if (input == "3") inventorySystem();
        else if (input == "4") portfolioSummary();
        else if (input == "0") {
            cout << GOLD << BOLD << "\n  Goodbye · Frank Oduro · KSTU · Ghana 🇬🇭\n\n" << RESET;
            break;
        }
        else cout << RED << "  ✗ Invalid option.\n" << RESET;
    }

    return 0;
}
