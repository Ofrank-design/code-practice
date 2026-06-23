# 🔷 Ghana Procurement Toolkit  TypeScript

> Typed interfaces, sorting algorithms, e-GP tender tracker, and spend dashboard all in one TypeScript file.

**By [Frank Oduro](https://ofrank-design.github.io) · KSTU BSc Procurement & Supply Chain Management · Ghana 🇬🇭**

---

## What's Inside

Four ideas in one clean file:

| Section | What it does |
|---|---|
| 🏷️ **Typed Interfaces** | Strongly typed models for Supplier, PurchaseOrder, Contract, Tender, SpendCategory |
| ⚙️ **Algorithms** | Bubble sort, quick sort, binary search, linear filter  all procurement-themed |
| 📋 **e-GP Tender Tracker** | Ghana e-GP tenders with method, stage, compliance status, Acts 663 & 914 |
| 📊 **Spend Dashboard** | Category breakdown with budget vs actual bar chart in the console |

---

## How to Run

```bash
# Option 1 — ts-node (easiest)
npm install -g ts-node typescript
ts-node procurement.ts

# Option 2 — compile then run
tsc procurement.ts
node procurement.js
```

---

## Sample Output

```
══════════════════════════════════════════════════════════
  GHANA PROCUREMENT TOOLKIT — TypeScript v1.0
  Frank Oduro · KSTU · Kumasi, Ghana 🇬🇭
  Interfaces · Algorithms · e-GP · Dashboard
══════════════════════════════════════════════════════════

  📦 SUPPLIER SCORECARD DASHBOARD
  Sorted by Score (Bubble Sort):

  Supplier                  Category       Score   Spend          Risk
  ──────────────────────────────────────────────────────────────────────
  KSTU Medical Stores       Medical        9.1     GHS 150,000    ✅ LOW
  Accra Supplies Ltd        Medical        8.2     GHS 320,000    ✅ LOW
  Ashanti Office Hub        Office         7.3     GHS 95,000     ✅ LOW
  Kumasi Tech Hub           IT             5.8     GHS 210,000    ⚠️  MED
  Greater Accra Maint.      Maintenance    4.5     GHS 140,000    ⚠️  MED
  Tema Port Logistics       Logistics      3.4     GHS 180,000    ❌ HIGH
```

---

## Algorithms Used

| Algorithm | Applied To | Complexity |
|---|---|---|
| Bubble Sort | Suppliers by score | O(n²) |
| Quick Sort | Purchase orders by value | O(n log n) |
| Binary Search | Find supplier by ID | O(log n) |
| Linear Filter | Tenders by method | O(n) |

---

## Ghana PPA Method Thresholds (Acts 663 & 914)

```typescript
if (value <= 50000)   → "Request for Quotations (RFQ)"
if (value <= 500000)  → "Restricted Tendering"
if (value <= 5000000) → "National Competitive Tendering"
else                  → "International Competitive Tendering"
```

---

## Interfaces

```typescript
interface Supplier     { id, name, category, score, spend, riskLevel }
interface PurchaseOrder{ poNumber, supplier, description, quantity, unitPrice, totalValue, status, date }
interface Contract     { reference, supplier, type, value, startDate, endDate, status }
interface Tender       { reference, title, value, stage, deadline, method, compliant }
interface SpendCategory{ name, budget, actual, variance, suppliers }
```

---

## About

Part of the `code-practice` polyglot repo — TypeScript after Java, showing typed systems thinking in a procurement context.

- 🌐 [Portfolio](https://ofrank-design.github.io)
- 🐙 [GitHub](https://github.com/Ofrank-design)

---

MIT License · ⭐ Star appreciated.

*Made in Kumasi, Ghana 🇬🇭*
