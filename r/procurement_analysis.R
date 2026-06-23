# ╔══════════════════════════════════════════════════════════════╗
# ║         GHANA PROCUREMENT ANALYTICS — R                     ║
# ║         Frank Oduro · KSTU BSc Procurement & SCM            ║
# ║         Statistics · Forecasting · Visualisation            ║
# ╚══════════════════════════════════════════════════════════════╝
#
# Covers:
# → Descriptive statistics on procurement spend
# → Demand forecasting (linear regression)
# → Supplier performance analysis
# → EOQ calculation in R
# → ABC classification
# → Spend visualisation (base R plots)
#
# Run: Rscript procurement_analysis.R
# Or open in RStudio and run line by line

cat("\n")
cat("═══════════════════════════════════════════════════════\n")
cat("  GHANA PROCUREMENT ANALYTICS — R v1.0\n")
cat("  Frank Oduro · KSTU · Kumasi, Ghana 🇬🇭\n")
cat("  Statistics · Forecasting · EOQ · ABC Analysis\n")
cat("═══════════════════════════════════════════════════════\n\n")

# ══════════════════════════════════════════════════════════
#  DATA — Ghana Procurement Context
# ══════════════════════════════════════════════════════════

# Monthly procurement spend (GHS) — 12 months
months      <- month.abb
spend       <- c(42000, 38500, 51000, 46000, 55000, 49000,
                 61000, 58000, 67000, 72000, 68000, 75000)

# Supplier data
suppliers <- data.frame(
  name        = c("Accra Supplies Ltd", "Kumasi Tech Hub", "Tema Port Logistics",
                  "KSTU Medical Stores", "Ashanti Office Hub", "Greater Accra Maint."),
  category    = c("Medical", "IT", "Logistics", "Medical", "Office", "Maintenance"),
  score       = c(8.2, 5.8, 3.4, 9.1, 7.3, 4.5),
  annual_spend= c(320000, 210000, 180000, 150000, 95000, 140000),
  on_time_pct = c(94, 78, 62, 97, 88, 71),
  quality_pct = c(96, 85, 70, 98, 92, 75),
  stringsAsFactors = FALSE
)

# Inventory items for EOQ & ABC
inventory <- data.frame(
  item         = c("Surgical Gloves", "Hand Sanitizer", "A4 Paper",
                   "Printer Toner", "Biro Pens", "Latex Gloves",
                   "Stapler", "File Folders", "Disinfectant", "Masks"),
  annual_demand= c(2400, 800, 1200, 300, 600, 1800, 150, 500, 960, 3600),
  unit_price   = c(12.50, 15.00, 8.00, 85.00, 3.50, 10.00, 25.00, 2.00, 18.00, 5.00),
  order_cost   = c(60, 35, 40, 50, 20, 55, 30, 15, 45, 40),
  hold_cost    = c(2.5, 3.0, 1.5, 8.0, 0.75, 2.0, 5.0, 0.4, 3.5, 1.0),
  stringsAsFactors = FALSE
)

# ══════════════════════════════════════════════════════════
#  1. DESCRIPTIVE STATISTICS — Monthly Spend
# ══════════════════════════════════════════════════════════

cat("──────────────────────────────────────────────────────\n")
cat("  1. DESCRIPTIVE STATISTICS — Monthly Spend (GHS)\n")
cat("──────────────────────────────────────────────────────\n")

cat(sprintf("  Total Annual Spend:   GHS %s\n",   format(sum(spend), big.mark=",")))
cat(sprintf("  Mean Monthly Spend:   GHS %s\n",   format(round(mean(spend)), big.mark=",")))
cat(sprintf("  Median Monthly Spend: GHS %s\n",   format(median(spend), big.mark=",")))
cat(sprintf("  Std Deviation:        GHS %s\n",   format(round(sd(spend)), big.mark=",")))
cat(sprintf("  Min Month:            %s — GHS %s\n", months[which.min(spend)], format(min(spend), big.mark=",")))
cat(sprintf("  Max Month:            %s — GHS %s\n", months[which.max(spend)], format(max(spend), big.mark=",")))
cat(sprintf("  Growth (Jan→Dec):     %.1f%%\n",   ((spend[12] - spend[1]) / spend[1]) * 100))

# Coefficient of variation
cv <- (sd(spend) / mean(spend)) * 100
cat(sprintf("  Coeff. of Variation:  %.1f%% — %s\n\n",
    cv, ifelse(cv < 20, "✅ Low volatility", ifelse(cv < 40, "⚠️  Medium volatility", "❌ High volatility"))))

# ══════════════════════════════════════════════════════════
#  2. DEMAND FORECASTING — Linear Regression
# ══════════════════════════════════════════════════════════

cat("──────────────────────────────────────────────────────\n")
cat("  2. DEMAND FORECASTING — Linear Regression\n")
cat("──────────────────────────────────────────────────────\n")

time   <- 1:12
model  <- lm(spend ~ time)
r2     <- summary(model)$r.squared
slope  <- coef(model)[2]
interc <- coef(model)[1]

cat(sprintf("  Model:    Spend = %.0f + %.0f × Month\n", interc, slope))
cat(sprintf("  R² Score: %.4f — %s\n",
    r2, ifelse(r2 > 0.9, "✅ Excellent fit", ifelse(r2 > 0.7, "⚠️  Good fit", "❌ Poor fit"))))
cat(sprintf("  Monthly growth trend: +GHS %s per month\n\n", format(round(slope), big.mark=",")))

# Forecast next 3 months
cat("  Forecast (next 3 months):\n")
for (i in 13:15) {
  forecast_val <- interc + slope * i
  month_name   <- month.abb[((i - 1) %% 12) + 1]
  cat(sprintf("  → Month %d (%s 2027): GHS %s\n",
      i, month_name, format(round(forecast_val), big.mark=",")))
}

# ══════════════════════════════════════════════════════════
#  3. EOQ CALCULATIONS
# ══════════════════════════════════════════════════════════

cat("\n──────────────────────────────────────────────────────\n")
cat("  3. EOQ CALCULATIONS — All Inventory Items\n")
cat("──────────────────────────────────────────────────────\n")

# Calculate EOQ for all items
inventory$eoq          <- round(sqrt((2 * inventory$annual_demand * inventory$order_cost) / inventory$hold_cost))
inventory$daily_demand <- inventory$annual_demand / 365
inventory$safety_stock <- round(inventory$daily_demand * 7)
inventory$rop          <- round(inventory$daily_demand * 14 + inventory$safety_stock)
inventory$orders_yr    <- round(inventory$annual_demand / inventory$eoq, 1)
inventory$annual_value <- inventory$annual_demand * inventory$unit_price

cat(sprintf("\n  %-18s %6s %8s %8s %8s\n", "Item", "EOQ", "SafeStk", "ROP", "Orders/Yr"))
cat(sprintf("  %s\n", paste(rep("─", 58), collapse="")))
for (i in 1:nrow(inventory)) {
  cat(sprintf("  %-18s %6d %8d %8d %8.1f\n",
      inventory$item[i], inventory$eoq[i],
      inventory$safety_stock[i], inventory$rop[i], inventory$orders_yr[i]))
}

# ══════════════════════════════════════════════════════════
#  4. ABC ANALYSIS — Pareto Classification
# ══════════════════════════════════════════════════════════

cat("\n──────────────────────────────────────────────────────\n")
cat("  4. ABC ANALYSIS — Pareto Classification\n")
cat("──────────────────────────────────────────────────────\n")

# Sort by annual value descending
inv_sorted       <- inventory[order(-inventory$annual_value), ]
total_val        <- sum(inv_sorted$annual_value)
inv_sorted$cum_pct <- cumsum(inv_sorted$annual_value) / total_val * 100
inv_sorted$abc   <- ifelse(inv_sorted$cum_pct <= 70, "A",
                    ifelse(inv_sorted$cum_pct <= 90, "B", "C"))

cat(sprintf("\n  %-18s %12s %8s %8s\n", "Item", "Ann. Value", "Cum %", "Class"))
cat(sprintf("  %s\n", paste(rep("─", 52), collapse="")))
for (i in 1:nrow(inv_sorted)) {
  cat(sprintf("  %-18s %12s %7.1f%% %8s\n",
      inv_sorted$item[i],
      paste0("GHS ", format(inv_sorted$annual_value[i], big.mark=",")),
      inv_sorted$cum_pct[i],
      inv_sorted$abc[i]))
}

a_items <- sum(inv_sorted$abc == "A")
b_items <- sum(inv_sorted$abc == "B")
c_items <- sum(inv_sorted$abc == "C")
cat(sprintf("\n  A items: %d (high value — review weekly)\n", a_items))
cat(sprintf("  B items: %d (medium value — review monthly)\n", b_items))
cat(sprintf("  C items: %d (low value — review quarterly)\n\n", c_items))

# ══════════════════════════════════════════════════════════
#  5. SUPPLIER PERFORMANCE ANALYSIS
# ══════════════════════════════════════════════════════════

cat("──────────────────────────────────────────────────────\n")
cat("  5. SUPPLIER PERFORMANCE ANALYSIS\n")
cat("──────────────────────────────────────────────────────\n")

# Sort by score
sup_sorted <- suppliers[order(-suppliers$score), ]

cat(sprintf("\n  %-22s %6s %8s %8s  Risk\n", "Supplier", "Score", "On-Time", "Quality"))
cat(sprintf("  %s\n", paste(rep("─", 60), collapse="")))
for (i in 1:nrow(sup_sorted)) {
  risk <- ifelse(sup_sorted$score[i] >= 7, "✅ LOW",
          ifelse(sup_sorted$score[i] >= 4, "⚠️  MED", "❌ HIGH"))
  cat(sprintf("  %-22s %6.1f %7d%% %7d%%  %s\n",
      sup_sorted$name[i], sup_sorted$score[i],
      sup_sorted$on_time_pct[i], sup_sorted$quality_pct[i], risk))
}

# Correlation: score vs on-time delivery
corr <- cor(suppliers$score, suppliers$on_time_pct)
cat(sprintf("\n  Score vs On-Time Correlation: %.3f — %s\n",
    corr, ifelse(abs(corr) > 0.8, "✅ Strong relationship", "⚠️  Moderate relationship")))

# Category spend breakdown
cat("\n  Spend by Category:\n")
cat_spend <- aggregate(annual_spend ~ category, data=suppliers, sum)
cat_spend <- cat_spend[order(-cat_spend$annual_spend), ]
max_spend <- max(cat_spend$annual_spend)
for (i in 1:nrow(cat_spend)) {
  bars <- round((cat_spend$annual_spend[i] / max_spend) * 25)
  bar  <- paste0(strrep("█", bars), strrep("░", 25 - bars))
  cat(sprintf("  %-14s %s GHS %s\n",
      cat_spend$category[i], bar,
      format(cat_spend$annual_spend[i], big.mark=",")))
}

# ══════════════════════════════════════════════════════════
#  6. VISUALISATION — Save Plots
# ══════════════════════════════════════════════════════════

cat("\n──────────────────────────────────────────────────────\n")
cat("  6. GENERATING PLOTS → saved as PNG files\n")
cat("──────────────────────────────────────────────────────\n")

# Plot 1 — Monthly Spend Trend
png("spend_trend.png", width=800, height=400, bg="white")
par(mar=c(4,5,3,2), bg="#f8f8f8")
plot(1:12, spend, type="b", col="#d4a843", lwd=2.5, pch=19, cex=1.2,
     xaxt="n", main="Monthly Procurement Spend — Ghana 2026",
     xlab="Month", ylab="Spend (GHS)", col.main="#0d2149",
     col.lab="#5a6a88", font.main=2)
axis(1, at=1:12, labels=months, cex.axis=0.85)
abline(model, col="#10b981", lwd=2, lty=2)
legend("topleft", legend=c("Actual Spend", "Trend Line"),
       col=c("#d4a843", "#10b981"), lwd=2, bty="n", cex=0.85)
grid(col="#e5e7eb", lty=1)
dev.off()
cat("  ✅ spend_trend.png saved\n")

# Plot 2 — Supplier Scorecard Bar Chart
png("supplier_scores.png", width=800, height=450, bg="white")
par(mar=c(6,4,3,2), bg="#f8f8f8")
colors <- ifelse(suppliers$score >= 7, "#10b981", ifelse(suppliers$score >= 4, "#f59e0b", "#ef4444"))
barplot(suppliers$score, names.arg=suppliers$name, col=colors, border=NA,
        main="Supplier Scorecard — Weighted KPI Scores",
        ylab="Score (0-10)", ylim=c(0, 10),
        col.main="#0d2149", col.lab="#5a6a88",
        las=2, cex.names=0.75, font.main=2)
abline(h=7, col="#10b981", lty=2, lwd=1.5)
abline(h=4, col="#ef4444", lty=2, lwd=1.5)
legend("topright", legend=c("Low Risk (≥7)", "Medium Risk (4-6)", "High Risk (<4)"),
       fill=c("#10b981","#f59e0b","#ef4444"), bty="n", cex=0.8)
dev.off()
cat("  ✅ supplier_scores.png saved\n")

# Plot 3 — ABC Analysis Pie Chart
png("abc_analysis.png", width=600, height=500, bg="white")
par(mar=c(2,2,3,2), bg="#f8f8f8")
abc_counts <- table(inv_sorted$abc)
abc_vals   <- tapply(inv_sorted$annual_value, inv_sorted$abc, sum)
pie(abc_vals, labels=paste0(names(abc_vals), "\n",
    round(abc_vals/sum(abc_vals)*100), "%"),
    col=c("#d4a843","#10b981","#6b7280"),
    main="ABC Analysis — Annual Value Distribution",
    col.main="#0d2149", font.main=2)
dev.off()
cat("  ✅ abc_analysis.png saved\n")

# ══════════════════════════════════════════════════════════
#  SUMMARY
# ══════════════════════════════════════════════════════════

cat("\n═══════════════════════════════════════════════════════\n")
cat("  ✅ ANALYSIS COMPLETE\n\n")
cat(sprintf("  Total Annual Spend:     GHS %s\n", format(sum(spend), big.mark=",")))
cat(sprintf("  Suppliers Analysed:     %d\n", nrow(suppliers)))
cat(sprintf("  Inventory Items (EOQ):  %d\n", nrow(inventory)))
cat(sprintf("  ABC Class A Items:      %d (high priority)\n", a_items))
cat(sprintf("  Forecast (Month 13):    GHS %s\n",
    format(round(interc + slope * 13), big.mark=",")))
cat(sprintf("  R² (Forecast Model):    %.4f\n", r2))
cat("\n  Portfolio: ofrank-design.github.io\n")
cat("  GitHub:    github.com/Ofrank-design\n")
cat("═══════════════════════════════════════════════════════\n\n")

