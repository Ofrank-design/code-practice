# 💎 Ghana Procurement Analytics — R

> Statistical analysis, demand forecasting, EOQ calculations, ABC classification, and visualisation — all in one R script.

**By [Frank Oduro](https://ofrank-design.github.io) · KSTU BSc Procurement & Supply Chain Management · Ghana 🇬🇭**

---

## What's Inside

| Section | What it does |
|---|---|
| 📊 **Descriptive Statistics** | Mean, median, SD, CV, growth rate on monthly spend |
| 📈 **Demand Forecasting** | Linear regression model — forecast next 3 months |
| 📦 **EOQ Calculations** | EOQ, safety stock, reorder point for 10 inventory items |
| 🗂️ **ABC Analysis** | Pareto classification — A/B/C items by annual value |
| ⚠️ **Supplier Analysis** | Score ranking, correlation analysis, category spend |
| 🖼️ **Visualisation** | 3 PNG charts saved automatically |

---

## How to Run

```r
# Option 1 — RStudio
# Open procurement_analysis.R → click Run

# Option 2 — Command line
Rscript procurement_analysis.R
```

No packages required — uses base R only.

---

## Output Files Generated

| File | What it shows |
|---|---|
| `spend_trend.png` | Monthly spend with regression trend line |
| `supplier_scores.png` | Supplier KPI bar chart — green/amber/red |
| `abc_analysis.png` | ABC classification pie chart |

---

## Sample Output

```
═══════════════════════════════════════════════════════
  GHANA PROCUREMENT ANALYTICS — R v1.0
  Frank Oduro · KSTU · Kumasi, Ghana 🇬🇭

  1. DESCRIPTIVE STATISTICS
  Total Annual Spend:   GHS 682,500
  Mean Monthly Spend:   GHS 56,875
  Growth (Jan→Dec):     78.6%
  R² Score:             0.9812 — ✅ Excellent fit

  Forecast (next 3 months):
  → Month 13 (Jan 2027): GHS 79,154
  → Month 14 (Feb 2027): GHS 82,681
  → Month 15 (Mar 2027): GHS 86,208
```

---

## EOQ Formula

```r
eoq <- sqrt((2 * annual_demand * order_cost) / hold_cost)
```

---

## ABC Classification Logic

```r
abc <- ifelse(cum_pct <= 70, "A",
       ifelse(cum_pct <= 90, "B", "C"))
```

- **Class A** — Top 70% of value → review weekly
- **Class B** — Next 20% of value → review monthly  
- **Class C** — Bottom 10% of value → review quarterly

---

## About

Part of the `code-practice` polyglot repo — R for statistical analysis after Java and TypeScript.

- 🌐 [Portfolio](https://ofrank-design.github.io)
- 🐙 [GitHub](https://github.com/Ofrank-design)

---

MIT License · ⭐ Star appreciated.

*Made in Kumasi, Ghana 🇬🇭*
