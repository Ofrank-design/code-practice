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
<p align="left">
  <a href="#" target="_blank">
    <img src="./icons/ghana-ppa.png" width="50" height="50" alt="Ghana PPA" style="margin-bottom: 5px;" />
  </a>
  <a href="#" target="_blank">
    <img src="./icons/ghana-egp.png" width="50" height="50" alt="Ghana e-GP" style="margin-bottom: 5px;" />
  </a>
  <a href="#" target="_blank">
    <img src="./icons/eoq.png" width="50" height="50" alt="EOQ Modelling" style="margin-bottom: 5px;" />
  </a>
  <a href="#" target="_blank">
    <img src="./icons/abc-analysis.png" width="50" height="50" alt="ABC Analysis" style="margin-bottom: 5px;" />
  </a>
  <a href="#" target="_blank">
    <img src="./icons/contract-management.png" width="50" height="50" alt="Contract Management" style="margin-bottom: 5px;" />
  </a>
  <a href="#" target="_blank">
    <img src="./icons/strategic-sourcing.png" width="50" height="50" alt="Strategic Sourcing" style="margin-bottom: 5px;" />
  </a>
</p>

#### 📊 Analytics & Tools
<p align="left">
  <a href="https://www.microsoft.com/microsoft-365/excel" target="_blank">
    <img src="./icons/excel.png" width="50" height="50" alt="Microsoft Excel" style="margin-bottom: 5px;" />
  </a>
  <a href="https://powerbi.microsoft.com/" target="_blank">
    <img src="./icons/powerbi.png" width="50" height="50" alt="Power BI" style="margin-bottom: 5px;" />
  </a>
  <a href="https://www.python.org/" target="_blank">
    <img src="./icons/python.png" width="50" height="50" alt="Python" style="margin-bottom: 5px;" />
  </a>
  <a href="https://developer.mozilla.org/en-US/docs/Web/JavaScript" target="_blank">
    <img src="./icons/javascript.png" width="50" height="50" alt="JavaScript" style="margin-bottom: 5px;" />
  </a>
  <a href="https://developer.mozilla.org/en-US/docs/Web/HTML" target="_blank">
    <img src="./icons/html5.png" width="50" height="50" alt="HTML5" style="margin-bottom: 5px;" />
  </a>
</p>

#### ⚙️ ERP Systems
<p align="left">
  <a href="https://www.sap.com/products/erp/mm.html" target="_blank">
    <img src="./icons/sap.png" width="50" height="50" alt="SAP MM" style="margin-bottom: 5px;" />
  </a>
  <a href="https://www.odoo.com/" target="_blank">
    <img src="./icons/odoo.png" width="50" height="50" alt="Odoo" style="margin-bottom: 5px;" />
  </a>
  <a href="https://www.oracle.com/cloud/" target="_blank">
    <img src="./icons/oracle.png" width="50" height="50" alt="Oracle Cloud" style="margin-bottom: 5px;" />
  </a>
  <a href="https://www.microsoft.com/en-us/dynamics-365" target="_blank">
    <img src="./icons/dynamics365.png" width="50" height="50" alt="MS Dynamics 365" style="margin-bottom: 5px;" />
  </a>
</p>

#### 🛠️ Dev & Productivity
<p align="left">
  <a href="https://github.com/ofrank-design" target="_blank">
    <img src="./icons/github.png" width="50" height="50" alt="GitHub" style="margin-bottom: 5px;" />
  </a>
  <a href="https://code.visualstudio.com/" target="_blank">
    <img src="./icons/vscode.png" width="50" height="50" alt="VS Code" style="margin-bottom: 5px;" />
  </a>
  <a href="https://learn.microsoft.com/" target="_blank">
    <img src="./icons/microsoft-learn.png" width="50" height="50" alt="Microsoft Learn" style="margin-bottom: 5px;" />
  </a>
  <a href="https://matplotlib.org/" target="_blank">
    <img src="./icons/matplotlib.png" width="50" height="50" alt="Matplotlib" style="margin-bottom: 5px;" />
  </a>
</p>
<img src="./icons/excel.png" width="50" height="50" alt="Excel" />
