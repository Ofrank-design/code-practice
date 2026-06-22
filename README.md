# ☕ Ghana Procurement Management System — Java

> A command-line procurement management system built in Java — linking all 7 portfolio projects into one program.

**By [Frank Oduro](https://ofrank-design.github.io) · KSTU BSc Procurement & Supply Chain Management · Ghana 🇬🇭**

---

## What It Does

One Java program. Seven procurement modules. All tied to real Ghana PPA Acts 663 & 914.

| Module | What it does | Portfolio Link |
|---|---|---|
| 📦 Inventory & EOQ | Calculate EOQ, safety stock, reorder point, ABC analysis | Project 4 |
| ⚠️ Supplier Scorecard | Weighted KPI scoring across delivery, quality, financial, compliance | Project 3 |
| 🔃 Purchase Orders | Create, view, approve POs with Ghana e-GP compliance | Project 1 |
| 📜 Contract Register | Draft and manage SLAs and framework agreements | Project 2 |
| 📊 Spend Analyzer | Category breakdown, portfolio value, spend dashboard | Project 5 |
| 🎯 Category Sourcing | Kraljic matrix, CIPS 7-step sourcing strategy | Project 6 |
| 🔒 Tender Risk Assessor | Acts 663 & 914 compliance checklist, risk rating | Project 7 |

---

## How to Run

```bash
# Compile
javac ProcurementSystem.java

# Run
java ProcurementSystem
```

Requires Java 11 or higher. No external dependencies.

---

## Sample Output

```
  ╔══════════════════════════════════════════════════════╗
  ║    GHANA PROCUREMENT MANAGEMENT SYSTEM  v1.0        ║
  ║    Frank Oduro · KSTU · Kumasi, Ghana 🇬🇭           ║
  ║    Built on: Java · Acts 663 & 914 · 7 Projects     ║
  ╚══════════════════════════════════════════════════════╝

  ══ MAIN MENU ══════════════════════════════
  [1] Inventory & EOQ Calculator    → Project 4
  [2] Supplier Scorecard Dashboard  → Project 3
  [3] Purchase Order Manager        → Project 1
  [4] Contract Register             → Project 2
  [5] Spend Analyzer                → Project 5
  [6] Category Sourcing Matrix      → Project 6
  [7] Tender Risk Assessor          → Project 7
  [8] Full Portfolio Summary
  [0] Exit
```

---

## EOQ Formula Used

```
EOQ = √(2DS / H)

D = Annual demand
S = Ordering cost per order
H = Holding cost per unit per year
```

Reorder Point = (Daily demand × Lead time) + Safety stock

---

## Supplier Scoring Weights

| Dimension | Weight |
|---|---|
| On-time delivery | 30% |
| Quality rejection rate | 30% |
| Financial stability | 20% |
| Regulatory compliance | 20% |

---

## Ghana PPA Compliance Thresholds

| Method | Threshold |
|---|---|
| Request for Quotations | Up to GHS 50,000 |
| Restricted Tendering | GHS 50,001 – 500,000 |
| National Competitive Tender | GHS 500,001 – 5,000,000 |
| International Competitive | Above GHS 5,000,000 |
| Single Source | Any value — PPA Board approval required |

---

## About

Built as part of the `code-practice` polyglot repo — demonstrating Java OOP in a procurement context before KSTU lectures begin.

- 🌐 [Portfolio](https://ofrank-design.github.io)
- 🐙 [GitHub](https://github.com/Ofrank-design)

---

MIT License — free to fork and adapt. ⭐ Star appreciated.

*Made in Kumasi, Ghana 🇬🇭*
#### 📦 Procurement & Supply Chain
![Ghana PPA](https://img.shields.io/badge/Ghana%20PPA%20Acts%20663%20%26%20914-0a4d2e?style=for-the-badge&logo=shield&logoColor=white)
![Ghana e-GP](https://img.shields.io/badge/Ghana%20e--GP%20Portal-1a6b3c?style=for-the-badge&logo=government&logoColor=white)
![EOQ Modelling](https://img.shields.io/badge/EOQ%20Modelling-16a34a?style=for-the-badge&logo=chartbar&logoColor=white)
![ABC Analysis](https://img.shields.io/badge/ABC%20Analysis-15803d?style=for-the-badge&logo=analytics&logoColor=white)
![Contract Management](https://img.shields.io/badge/Contract%20Management-166534?style=for-the-badge&logo=clipboard&logoColor=white)
![Strategic Sourcing](https://img.shields.io/badge/Strategic%20Sourcing-14532d?style=for-the-badge&logo=search&logoColor=white)
#### 📊 Analytics & Tools
![Microsoft Excel](https://img.shields.io/badge/Microsoft%20Excel-217346?style=for-the-badge&logo=microsoft-excel&logoColor=white)
![Power BI](https://img.shields.io/badge/Power%20BI-F2C811?style=for-the-badge&logo=powerbi&logoColor=black)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)
![HTML5](https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white)
