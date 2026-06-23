/**
 * ╔══════════════════════════════════════════════════════════════╗
 * ║         GHANA PROCUREMENT TOOLKIT — TypeScript              ║
 * ║         Frank Oduro · KSTU BSc Procurement & SCM            ║
 * ║         Typed interfaces · Algorithms · e-GP · Dashboard    ║
 * ╚══════════════════════════════════════════════════════════════╝
 *
 * Covers:
 * → Typed interfaces for Supplier, PO, Contract, Tender
 * → Sorting & searching algorithms (procurement context)
 * → Ghana e-GP Tender tracker
 * → Mini spend dashboard in the console
 *
 * Run: npx ts-node procurement.ts
 * Or:  tsc procurement.ts && node procurement.js
 */

// ══════════════════════════════════════════════════════════
//  INTERFACES — Typed Data Models
// ══════════════════════════════════════════════════════════

interface Supplier {
  id:         number;
  name:       string;
  category:   string;
  score:      number;   // 0–10 weighted KPI score
  spend:      number;   // GHS annual spend
  riskLevel:  "LOW" | "MEDIUM" | "HIGH";
}

interface PurchaseOrder {
  poNumber:    string;
  supplier:    string;
  description: string;
  quantity:    number;
  unitPrice:   number;
  totalValue:  number;
  status:      "PENDING" | "APPROVED" | "REJECTED" | "DELIVERED";
  date:        string;
}

interface Contract {
  reference:   string;
  supplier:    string;
  type:        "SLA" | "FRAMEWORK" | "SUPPLY" | "CONSULTANCY";
  value:       number;
  startDate:   string;
  endDate:     string;
  status:      "DRAFT" | "ACTIVE" | "EXPIRED" | "TERMINATED";
}

interface Tender {
  reference:   string;
  title:       string;
  value:       number;
  stage:       "ADVERTISED" | "BID_OPEN" | "EVALUATION" | "AWARDED" | "CLOSED";
  deadline:    string;
  method:      "RFQ" | "RESTRICTED" | "NATIONAL" | "INTERNATIONAL" | "SINGLE_SOURCE";
  compliant:   boolean;
}

interface SpendCategory {
  name:       string;
  budget:     number;
  actual:     number;
  variance:   number;
  suppliers:  number;
}

// ══════════════════════════════════════════════════════════
//  SEED DATA — Ghana Context
// ══════════════════════════════════════════════════════════

const suppliers: Supplier[] = [
  { id: 1, name: "Accra Supplies Ltd",   category: "Medical",    score: 8.2, spend: 320000, riskLevel: "LOW"    },
  { id: 2, name: "Kumasi Tech Hub",      category: "IT",         score: 5.8, spend: 210000, riskLevel: "MEDIUM" },
  { id: 3, name: "Tema Port Logistics",  category: "Logistics",  score: 3.4, spend: 180000, riskLevel: "HIGH"   },
  { id: 4, name: "KSTU Medical Stores",  category: "Medical",    score: 9.1, spend: 150000, riskLevel: "LOW"    },
  { id: 5, name: "Ashanti Office Hub",   category: "Office",     score: 7.3, spend: 95000,  riskLevel: "LOW"    },
  { id: 6, name: "Greater Accra Maint.", category: "Maintenance",score: 4.5, spend: 140000, riskLevel: "MEDIUM" },
];

const purchaseOrders: PurchaseOrder[] = [
  { poNumber: "PO-2026-001", supplier: "Accra Supplies Ltd",  description: "Surgical Gloves (500 boxes)", quantity: 500, unitPrice: 12.50, totalValue: 6250,    status: "APPROVED",  date: "2026-06-01" },
  { poNumber: "PO-2026-002", supplier: "Kumasi Tech Hub",     description: "Laptop Computers",            quantity: 5,   unitPrice: 3500,  totalValue: 17500,   status: "PENDING",   date: "2026-06-05" },
  { poNumber: "PO-2026-003", supplier: "Ashanti Office Hub",  description: "A4 Paper (200 reams)",        quantity: 200, unitPrice: 8,     totalValue: 1600,    status: "DELIVERED", date: "2026-05-20" },
  { poNumber: "PO-2026-004", supplier: "Tema Port Logistics", description: "Freight Services — Kumasi",   quantity: 1,   unitPrice: 45000, totalValue: 45000,   status: "APPROVED",  date: "2026-06-10" },
  { poNumber: "PO-2026-005", supplier: "KSTU Medical Stores", description: "Hand Sanitizer (500ml)",      quantity: 300, unitPrice: 15,    totalValue: 4500,    status: "PENDING",   date: "2026-06-12" },
];

const contracts: Contract[] = [
  { reference: "CON-2026-001", supplier: "Accra Supplies Ltd",   type: "SUPPLY",      value: 250000, startDate: "2026-01-01", endDate: "2026-12-31", status: "ACTIVE"  },
  { reference: "CON-2026-002", supplier: "Kumasi Tech Hub",      type: "SLA",         value: 180000, startDate: "2026-03-01", endDate: "2027-02-28", status: "ACTIVE"  },
  { reference: "CON-2026-003", supplier: "Tema Port Logistics",  type: "FRAMEWORK",   value: 500000, startDate: "2026-01-01", endDate: "2026-12-31", status: "ACTIVE"  },
  { reference: "CON-2026-004", supplier: "Ashanti Office Hub",   type: "SUPPLY",      value: 48000,  startDate: "2026-06-01", endDate: "2026-11-30", status: "DRAFT"   },
];

const tenders: Tender[] = [
  { reference: "MOH/2026/047", title: "Supply of Surgical Gloves — MOH",       value: 125000, stage: "BID_OPEN",   deadline: "2026-07-05", method: "RESTRICTED",     compliant: true  },
  { reference: "GES/2026/012", title: "IT Equipment — Ghana Education Service", value: 380000, stage: "EVALUATION", deadline: "2026-08-15", method: "NATIONAL",       compliant: true  },
  { reference: "KNUST/2026/3", title: "Office Furniture — KNUST",               value: 55000,  stage: "AWARDED",    deadline: "2026-05-30", method: "RESTRICTED",     compliant: true  },
  { reference: "MOH/2026/051", title: "Medical Equipment Maintenance",          value: 28000,  stage: "ADVERTISED", deadline: "2026-07-20", method: "RFQ",            compliant: false },
  { reference: "GPHA/2026/08", title: "Port Logistics Framework — Tema",        value: 6200000,stage: "BID_OPEN",   deadline: "2026-09-01", method: "INTERNATIONAL",  compliant: true  },
];

// ══════════════════════════════════════════════════════════
//  ALGORITHMS — Sorting & Searching (Procurement Context)
// ══════════════════════════════════════════════════════════

// 1. Sort suppliers by score (bubble sort — educational)
function bubbleSortSuppliers(data: Supplier[]): Supplier[] {
  const arr = [...data];
  for (let i = 0; i < arr.length - 1; i++) {
    for (let j = 0; j < arr.length - i - 1; j++) {
      if (arr[j].score < arr[j + 1].score) {
        [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]];
      }
    }
  }
  return arr;
}

// 2. Sort POs by value (quick sort)
function quickSortPOs(data: PurchaseOrder[]): PurchaseOrder[] {
  if (data.length <= 1) return data;
  const pivot = data[Math.floor(data.length / 2)].totalValue;
  const left  = data.filter(po => po.totalValue > pivot);
  const mid   = data.filter(po => po.totalValue === pivot);
  const right = data.filter(po => po.totalValue < pivot);
  return [...quickSortPOs(left), ...mid, ...quickSortPOs(right)];
}

// 3. Binary search suppliers by ID
function binarySearchSupplier(data: Supplier[], targetId: number): Supplier | null {
  const sorted = [...data].sort((a, b) => a.id - b.id);
  let lo = 0, hi = sorted.length - 1;
  while (lo <= hi) {
    const mid = Math.floor((lo + hi) / 2);
    if (sorted[mid].id === targetId) return sorted[mid];
    sorted[mid].id < targetId ? lo = mid + 1 : hi = mid - 1;
  }
  return null;
}

// 4. Filter tenders by method (linear search)
function filterTendersByMethod(data: Tender[], method: Tender["method"]): Tender[] {
  return data.filter(t => t.method === method);
}

// 5. EOQ calculation (typed)
function calculateEOQ(D: number, S: number, H: number): {
  eoq: number; safetyStock: number; rop: number; ordersPerYear: number; annualCost: number;
} {
  const eoq          = Math.sqrt((2 * D * S) / H);
  const dailyDemand  = D / 365;
  const safetyStock  = dailyDemand * 7;
  const rop          = dailyDemand * 14 + safetyStock;
  const ordersPerYear = D / eoq;
  const annualCost   = (ordersPerYear * S) + ((eoq / 2) * H);
  return { eoq, safetyStock, rop, ordersPerYear, annualCost };
}

// 6. Supplier risk classifier
function classifyRisk(score: number): Supplier["riskLevel"] {
  if (score >= 7) return "LOW";
  if (score >= 4) return "MEDIUM";
  return "HIGH";
}

// 7. PPA method recommender (Acts 663 & 914)
function recommendProcurementMethod(value: number): string {
  if (value <= 50000)      return "Request for Quotations (RFQ) — Min. 3 quotes required";
  if (value <= 500000)     return "Restricted Tendering — Invite selected suppliers";
  if (value <= 5000000)    return "National Competitive Tendering — Publish on Ghana e-GP";
  return                          "International Competitive Tendering — ICB required";
}

// ══════════════════════════════════════════════════════════
//  DASHBOARD — Console Output
// ══════════════════════════════════════════════════════════

const GHS = (n: number): string => `GHS ${n.toLocaleString("en-GH", { minimumFractionDigits: 2 })}`;
const bar = (val: number, max: number, width: number = 25): string => {
  const filled = Math.round((val / max) * width);
  return "█".repeat(filled) + "░".repeat(width - filled);
};
const line = (char: string = "─", len: number = 55): string => char.repeat(len);

function printBanner(): void {
  console.log("\n" + "═".repeat(58));
  console.log("  GHANA PROCUREMENT TOOLKIT — TypeScript v1.0");
  console.log("  Frank Oduro · KSTU · Kumasi, Ghana 🇬🇭");
  console.log("  Interfaces · Algorithms · e-GP · Dashboard");
  console.log("═".repeat(58));
  console.log("  github.com/Ofrank-design · ofrank-design.github.io\n");
}

function printSupplierDashboard(): void {
  console.log("\n" + line("═") + "\n  📦 SUPPLIER SCORECARD DASHBOARD\n" + line());
  console.log("  Sorted by Score (Bubble Sort):\n");
  console.log(`  ${"Supplier".padEnd(25)} ${"Category".padEnd(14)} ${"Score".padEnd(7)} ${"Spend".padEnd(14)} Risk`);
  console.log("  " + line("─", 70));

  const sorted = bubbleSortSuppliers(suppliers);
  sorted.forEach(s => {
    const risk = s.riskLevel === "LOW" ? "✅ LOW" : s.riskLevel === "MEDIUM" ? "⚠️  MED" : "❌ HIGH";
    console.log(`  ${s.name.padEnd(25)} ${s.category.padEnd(14)} ${s.score.toFixed(1).padEnd(7)} ${GHS(s.spend).padEnd(14)} ${risk}`);
  });

  const avgScore = suppliers.reduce((sum, s) => sum + s.score, 0) / suppliers.length;
  const totalSpend = suppliers.reduce((sum, s) => sum + s.spend, 0);
  const highRisk = suppliers.filter(s => s.riskLevel === "HIGH").length;
  console.log("\n  " + line("─", 70));
  console.log(`  Avg Score: ${avgScore.toFixed(1)}/10 · Total Spend: ${GHS(totalSpend)} · High Risk: ${highRisk} supplier(s)`);
}

function printPODashboard(): void {
  console.log("\n" + line("═") + "\n  🔃 PURCHASE ORDERS — Sorted by Value (Quick Sort)\n" + line());
  console.log(`  ${"PO Number".padEnd(14)} ${"Supplier".padEnd(22)} ${"Value".padEnd(14)} Status`);
  console.log("  " + line("─", 65));

  const sorted = quickSortPOs(purchaseOrders);
  sorted.forEach(po => {
    const status = po.status === "APPROVED" ? "✅ APPROVED" : po.status === "PENDING" ? "⏳ PENDING" : po.status === "DELIVERED" ? "📦 DELIVERED" : "❌ REJECTED";
    console.log(`  ${po.poNumber.padEnd(14)} ${po.supplier.padEnd(22)} ${GHS(po.totalValue).padEnd(14)} ${status}`);
  });

  const total = purchaseOrders.reduce((sum, po) => sum + po.totalValue, 0);
  const approved = purchaseOrders.filter(po => po.status === "APPROVED").reduce((sum, po) => sum + po.totalValue, 0);
  console.log("\n  " + line("─", 65));
  console.log(`  Total PO Value: ${GHS(total)} · Approved: ${GHS(approved)}`);
}

function printTenderTracker(): void {
  console.log("\n" + line("═") + "\n  📋 GHANA e-GP TENDER TRACKER — Acts 663 & 914\n" + line());
  console.log(`  ${"Reference".padEnd(16)} ${"Title".padEnd(32)} ${"Value".padEnd(14)} Stage`);
  console.log("  " + line("─", 75));

  tenders.forEach(t => {
    const stage  = t.stage === "AWARDED" ? "✅ AWARDED" : t.stage === "EVALUATION" ? "🔍 EVAL" : t.stage === "BID_OPEN" ? "📬 BID OPEN" : t.stage === "ADVERTISED" ? "📢 ADVERTISED" : "🔒 CLOSED";
    const title  = t.title.length > 30 ? t.title.substring(0, 30) + ".." : t.title;
    console.log(`  ${t.reference.padEnd(16)} ${title.padEnd(32)} ${GHS(t.value).padEnd(14)} ${stage}`);

    const method = recommendProcurementMethod(t.value);
    console.log(`  ${"".padEnd(16)} Method: ${t.method} · ${t.compliant ? "✅ Compliant" : "❌ Non-compliant"}`);
    console.log(`  ${"".padEnd(16)} Deadline: ${t.deadline}\n`);
  });
}

function printSpendDashboard(): void {
  console.log("\n" + line("═") + "\n  📊 SPEND DASHBOARD — Category Analysis\n" + line());

  const categories: SpendCategory[] = [
    { name: "Medical Supplies",  budget: 350000, actual: 320000, variance: 30000,  suppliers: 2 },
    { name: "IT Equipment",      budget: 200000, actual: 210000, variance: -10000, suppliers: 1 },
    { name: "Office Supplies",   budget: 100000, actual: 95000,  variance: 5000,   suppliers: 1 },
    { name: "Maintenance",       budget: 160000, actual: 140000, variance: 20000,  suppliers: 1 },
    { name: "Logistics",         budget: 170000, actual: 180000, variance: -10000, suppliers: 1 },
  ];

  const maxBudget = Math.max(...categories.map(c => c.budget));
  categories.forEach(c => {
    const pct      = ((c.actual / c.budget) * 100).toFixed(0);
    const status   = c.variance >= 0 ? `✅ Under GHS ${c.variance.toLocaleString()}` : `⚠️  Over GHS ${Math.abs(c.variance).toLocaleString()}`;
    console.log(`  ${c.name.padEnd(20)} ${bar(c.actual, maxBudget)} ${pct}%`);
    console.log(`  ${"".padEnd(20)} Budget: ${GHS(c.budget)} · Actual: ${GHS(c.actual)} · ${status}\n`);
  });

  const totalBudget = categories.reduce((s, c) => s + c.budget, 0);
  const totalActual = categories.reduce((s, c) => s + c.actual, 0);
  console.log("  " + line("─", 60));
  console.log(`  Total Budget: ${GHS(totalBudget)} · Total Actual: ${GHS(totalActual)}`);
  console.log(`  ${totalActual <= totalBudget ? "✅ Within budget" : "⚠️  Over budget"} · Variance: ${GHS(Math.abs(totalBudget - totalActual))}`);
}

function printAlgorithmDemo(): void {
  console.log("\n" + line("═") + "\n  ⚙️  ALGORITHM DEMOS\n" + line());

  // Binary search demo
  console.log("  Binary Search — Find Supplier by ID:");
  const found = binarySearchSupplier(suppliers, 3);
  console.log(found ? `  ✅ Found: ${found.name} (Score: ${found.score})` : "  ✗ Not found");

  // Filter demo
  console.log("\n  Linear Search — Filter Tenders by Method (NATIONAL):");
  const national = filterTendersByMethod(tenders, "NATIONAL");
  national.forEach(t => console.log(`  → ${t.reference}: ${t.title}`));

  // EOQ demo
  console.log("\n  EOQ Calculation — Surgical Gloves:");
  const eoq = calculateEOQ(2400, 60, 2.5);
  console.log(`  EOQ: ${eoq.eoq.toFixed(0)} units · Safety Stock: ${eoq.safetyStock.toFixed(0)} units`);
  console.log(`  Reorder Point: ${eoq.rop.toFixed(0)} units · Annual Cost: ${GHS(eoq.annualCost)}`);

  // PPA method recommender
  console.log("\n  PPA Method Recommender — Acts 663 & 914:");
  [25000, 180000, 750000, 7500000].forEach(val => {
    console.log(`  ${GHS(val).padEnd(20)} → ${recommendProcurementMethod(val)}`);
  });
}

// ══════════════════════════════════════════════════════════
//  MAIN — Run Everything
// ══════════════════════════════════════════════════════════

function main(): void {
  printBanner();
  printSupplierDashboard();
  printPODashboard();
  printTenderTracker();
  printSpendDashboard();
  printAlgorithmDemo();

  console.log("\n" + "═".repeat(58));
  console.log("  ✅ Ghana Procurement Toolkit — TypeScript Complete");
  console.log("  Portfolio: ofrank-design.github.io");
  console.log("  GitHub:    github.com/Ofrank-design");
  console.log("═".repeat(58) + "\n");
}

main();

