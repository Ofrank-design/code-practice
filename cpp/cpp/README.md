# ⚡ Ghana Procurement Engine — C++

> Logistics route optimizer, supplier sorting engine, inventory management system, and portfolio summary — all in one C++ file.

**By [Frank Oduro](https://ofrank-design.github.io) · KSTU BSc Procurement & Supply Chain Management · Ghana 🇬🇭**

---

## What's Inside

| Module | Algorithm / Feature | Project Link |
|---|---|---|
| 🚚 **Route Optimizer** | Dijkstra's shortest path — Ghana cities | Project 8 |
| ⚙️ **Supplier Sorter** | Bubble, Selection, Merge sort compared | Project 3 |
| 📦 **Inventory System** | EOQ, ABC analysis, safety stock, ROP | Project 4 |
| 📋 **Portfolio Summary** | All 7 projects linked | All Projects |

---

## How to Run

```bash
# Compile
g++ -o procurement procurement.cpp -std=c++17

# Run
./procurement
```

Requires g++ with C++17 support. No external libraries.

---

## Algorithms Used

| Algorithm | Applied To | Complexity |
|---|---|---|
| Dijkstra's | Shortest logistics route between Ghana cities | O((V+E) log V) |
| Bubble Sort | Suppliers by weighted KPI score | O(n²) |
| Selection Sort | Suppliers by annual spend | O(n²) |
| Merge Sort | Suppliers alphabetically | O(n log n) |
| EOQ Formula | All inventory items | O(n) |

---

## Ghana Cities in the Route Network

```
[0] Accra      (Greater Accra)
[1] Kumasi     (Ashanti)
[2] Tema       (Greater Accra)
[3] Takoradi   (Western)
[4] Tamale     (Northern)
[5] Cape Coast (Central)
```

Shortest paths calculated using Dijkstra's algorithm on real road distances.

---

## C++ Features Used

- Structs with methods
- STL vectors, maps, priority_queue
- Template functions
- ANSI terminal colours
- Algorithm implementations from scratch
- `<chrono>` timing

---

## EOQ Formula

```cpp
double eoq() const {
    return sqrt((2.0 * annualDemand * orderCost) / holdCost);
}
```

---

## About

Part of the `code-practice` polyglot repo — C++ for performance-critical logistics and sorting after Java, TypeScript and R.

- 🌐 [Portfolio](https://ofrank-design.github.io)
- 🐙 [GitHub](https://github.com/Ofrank-design)

---

MIT License · ⭐ Star appreciated.

*Made in Kumasi, Ghana 🇬🇭*
