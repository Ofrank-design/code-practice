# ☕ Ghana Procurement Management System  Java

> A command-line procurement management system built in Java  linking all 7 portfolio projects into one program.

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

<h2 align="center"> 📈 GitHub Stats </h2>

<p align="center">
  <img src="https://github-readme-stats.vercel.app/api?username=Ofrank-design&show_icons=true&theme=chartreuse-dark&hide_border=true&count_private=true" width="48%"/>
  <img src="https://github-readme-streak-stats.herokuapp.com/?user=Ofrank-design&theme=chartreuse-dark&hide_border=true" width="48%"/>
</p>

<p align="center">
  <img src="https://github-readme-stats.vercel.app/api/top-langs/?username=Ofrank-design&theme=chartreuse-dark&hide_border=true&layout=compact" width="50%"/>
</p>

---

<h2 align="center">🏆 GitHub Trophies </h2>

<p align="center">
  <img src="https://github-trophies.vercel.app/?username=Ofrank-design&theme=matrix&no-frame=true&no-bg=true&column=6"/>
</p>


<h2 align="center">📈 Contribution Graph </h2>

<p align="center">
  <img src="https://github-readme-activity-graph.vercel.app/graph?username=Ofrank-design&theme=tokyo-night&hide_border=true"/>
</p>


## About

Built as part of the `code-practice` polyglot repo  demonstrating Java OOP in a procurement context before KSTU lectures begin.

- 🌐 [Portfolio](https://ofrank-design.github.io)
- 🐙 [GitHub](https://github.com/Ofrank-design)

---

MIT License free to fork and adapt. ⭐ Star appreciated.

*Made in Kumasi, Ghana 🇬🇭*
