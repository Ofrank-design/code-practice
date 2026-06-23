# 🐍 Ghana Procurement Analytics — Python

> OOP classes, data structures, algorithms, spend analytics, and tender tracking — all in one Python file.

**By [Frank Oduro](https://ofrank-design.github.io) · KSTU BSc Procurement & Supply Chain Management · Ghana 🇬🇭**

---

## What's Inside

| Module | What it covers | Project Link |
|---|---|---|
| 🗂️ **Data Structures** | Stack, Queue, Heap, Dictionary, Set — procurement-themed | All |
| ⚠️ **Supplier Dashboard** | Sorted scorecard, weighted KPI, risk classification | Project 3 |
| 📦 **Inventory & EOQ** | EOQ, safety stock, reorder point, ABC analysis | Project 4 |
| 🔃 **Purchase Orders** | P2P workflow, Acts 663 & 914 method thresholds | Project 1 |
| 🔒 **Tender Risk Tracker** | Ghana e-GP tenders, compliance, risk rating | Project 7 |
| 📊 **Spend Analytics** | Monthly trend, statistics, linear regression forecast | Project 5 |

---

## How to Run

```bash
python procurement.py
```

No external packages required — pure Python standard library only.

---

## Sample Output

```
  ╔══════════════════════════════════════════════════════╗
  ║    GHANA PROCUREMENT ANALYTICS — Python  v1.0      ║
  ║    Frank Oduro · KSTU · Kumasi, Ghana 🇬🇭           ║
  ╚══════════════════════════════════════════════════════╝

  ══ MAIN MENU ══════════════════════════════
  [1] Data Structures Demo   → Stack · Queue · Heap · Dict
  [2] Supplier Dashboard     → Project 3
  [3] Inventory & EOQ        → Project 4
  [4] Purchase Orders        → Project 1
  [5] Tender Risk Tracker    → Project 7
  [6] Spend Analytics        → Project 5
  [0] Exit
```

---

## Python Features Used

- `@dataclass` decorators
- Type hints throughout
- `heapq` for min-heap priority queue
- `collections.deque` for FIFO queue
- List comprehensions and generator expressions
- Lambda functions for sorting
- Manual linear regression (no numpy)
- ANSI terminal colours

---

## Data Structures Demonstrated

| Structure | Use Case |
|---|---|
| **Stack (list)** | PO approval queue — LIFO processing |
| **Queue (deque)** | Tender processing — FIFO order |
| **Dictionary** | Spend aggregation by category |
| **Min-Heap** | Find lowest-scoring suppliers fast |
| **Set** | Unique supplier categories |

---

## EOQ Class Method

```python
def eoq(self) -> float:
    return math.sqrt((2 * self.annual_demand * self.order_cost) / self.hold_cost)
```

---

## Ghana PPA Method Logic

```python
def ppa_method(self) -> str:
    v = self.total_value()
    if v <= 50000:   return "RFQ (min. 3 quotes)"
    if v <= 500000:  return "Restricted Tendering"
    if v <= 5000000: return "National Competitive"
    return "International Competitive"
```

---

## About

Part of the `code-practice` polyglot repo — Python for data structures and analytics after Java, TypeScript, R and C++.

- 🌐 [Portfolio](https://ofrank-design.github.io)
- 🐙 [GitHub](https://github.com/Ofrank-design)

---

MIT License · ⭐ Star appreciated.

*Made in Kumasi, Ghana 🇬🇭*
