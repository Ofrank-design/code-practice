<svg width="100%" height="220" viewBox="0 0 1200 220" xmlns="http://www.w3.org/2000/svg">
  <defs>
    <linearGradient id="neonGradient" x1="0%" y1="0%" x2="100%" y2="0%">
      <stop offset="0%" stop-color="#00F5FF">
        <animate attributeName="stop-color" values="#00F5FF;#FF00E5;#39FF14;#00F5FF" dur="6s" repeatCount="indefinite"/>
      </stop>
      <stop offset="100%" stop-color="#FF00E5">
        <animate attributeName="stop-color" values="#FF00E5;#39FF14;#00F5FF;#FF00E5" dur="6s" repeatCount="indefinite"/>
      </stop>
    </linearGradient>

    <filter id="glow">
      <feGaussianBlur stdDeviation="4" result="blur"/>
      <feMerge>
        <feMergeNode in="blur"/>
        <feMergeNode in="SourceGraphic"/>
      </feMerge>
    </filter>

    <style>
      .title {
        font-family: 'Courier New', monospace;
        font-size: 56px;
        font-weight: 700;
        letter-spacing: 4px;
      }
      .subtitle {
        font-family: 'Courier New', monospace;
        font-size: 22px;
        letter-spacing: 2px;
      }
    </style>
  </defs>

  <rect width="1200" height="220" rx="24" fill="#050816"/>
  <circle cx="150" cy="70" r="3" fill="#00F5FF">
    <animate attributeName="opacity" values="0;1;0" dur="2s" repeatCount="indefinite"/>
  </circle>
  <circle cx="1080" cy="150" r="3" fill="#FF00E5">
    <animate attributeName="opacity" values="0;1;0" dur="2.5s" repeatCount="indefinite"/>
  </circle>
  <circle cx="980" cy="50" r="3" fill="#39FF14">
    <animate attributeName="opacity" values="0;1;0" dur="3s" repeatCount="indefinite"/>
  </circle>

  <text x="50%" y="95" text-anchor="middle" class="title" fill="url(#neonGradient)" filter="url(#glow)">
    OFRANK-DESIGN
  </text>

  <text x="50%" y="145" text-anchor="middle" class="subtitle" fill="#B8C4FF" opacity="0.95">
    Procurement • Supply Chain • Data • Dev
  </text>

  <text x="50%" y="180" text-anchor="middle" class="subtitle" fill="#00F5FF" opacity="0.85">
    Building a professional portfolio with code and strategy
  </text>
</svg>
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
