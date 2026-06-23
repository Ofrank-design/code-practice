"""
╔══════════════════════════════════════════════════════════════╗
║         GHANA PROCUREMENT ANALYTICS — Python                ║
║         Frank Oduro · KSTU BSc Procurement & SCM            ║
║         Data Structures · OOP · Analytics · Algorithms      ║
╚══════════════════════════════════════════════════════════════╝

Covers:
→ OOP classes for Supplier, Inventory, PurchaseOrder, Tender
→ Data structures (lists, dicts, stacks, queues)
→ Algorithms (sorting, searching, EOQ, ABC, spend analysis)
→ Links all 7 portfolio projects
→ Console dashboard with charts

Run: python procurement.py
"""

import math
import heapq
from collections import deque
from dataclasses import dataclass, field
from typing import Optional

# ── ANSI COLORS ──────────────────────────────────────────
GOLD   = "\033[33m"
GREEN  = "\033[32m"
CYAN   = "\033[36m"
RED    = "\033[31m"
PURPLE = "\033[35m"
BOLD   = "\033[1m"
DIM    = "\033[2m"
RESET  = "\033[0m"
WHITE  = "\033[37m"

def ghs(amount: float) -> str:
    return f"GHS {amount:,.2f}"

def bar(value: float, max_val: float, width: int = 25) -> str:
    filled = round((value / max_val) * width) if max_val > 0 else 0
    return "█" * filled + "░" * (width - filled)

def section(title: str, subtitle: str) -> None:
    print(f"\n{GOLD}{BOLD}  ╔══════════════════════════════════════════════╗")
    print(f"  ║  {title:<44}║")
    print(f"  ╚══════════════════════════════════════════════╝{RESET}")
    print(f"{DIM}  {subtitle}{RESET}")

def divider(length: int = 60) -> None:
    print(f"{DIM}  {'─' * length}{RESET}")

# ══════════════════════════════════════════════════════════
#  OOP CLASSES
# ══════════════════════════════════════════════════════════

@dataclass
class Supplier:
    id:          int
    name:        str
    category:    str
    delivery:    float  # score /10
    quality:     float
    financial:   float
    compliance:  float
    spend:       float  # annual GHS

    def weighted_score(self) -> float:
        return (self.delivery   * 0.30 +
                self.quality    * 0.30 +
                self.financial  * 0.20 +
                self.compliance * 0.20)

    def risk_level(self) -> str:
        s = self.weighted_score()
        if s >= 7: return f"{GREEN}LOW{RESET}"
        if s >= 4: return f"{GOLD}MEDIUM{RESET}"
        return f"{RED}HIGH{RESET}"

    def __lt__(self, other):
        return self.weighted_score() > other.weighted_score()


@dataclass
class InventoryItem:
    name:          str
    stock:         int
    unit_price:    float
    annual_demand: float
    order_cost:    float
    hold_cost:     float
    abc_class:     str = field(default="C")

    def eoq(self) -> float:
        return math.sqrt((2 * self.annual_demand * self.order_cost) / self.hold_cost)

    def safety_stock(self, buffer_days: int = 7) -> float:
        return (self.annual_demand / 365) * buffer_days

    def reorder_point(self, lead_time: int = 14) -> float:
        daily = self.annual_demand / 365
        return (daily * lead_time) + self.safety_stock()

    def annual_value(self) -> float:
        return self.annual_demand * self.unit_price

    def orders_per_year(self) -> float:
        return self.annual_demand / self.eoq()


@dataclass
class PurchaseOrder:
    po_number:   str
    supplier:    str
    description: str
    quantity:    int
    unit_price:  float
    status:      str = "PENDING"

    def total_value(self) -> float:
        return self.quantity * self.unit_price

    def ppa_method(self) -> str:
        v = self.total_value()
        if v <= 50000:   return "RFQ (min. 3 quotes)"
        if v <= 500000:  return "Restricted Tendering"
        if v <= 5000000: return "National Competitive"
        return "International Competitive"


@dataclass
class Tender:
    reference:  str
    title:      str
    value:      float
    stage:      str
    method:     str
    deadline:   str
    compliant:  bool = True

    def risk_score(self) -> int:
        score = 0
        if self.compliant:       score += 2
        if self.value <= 500000: score += 2
        if self.stage != "BID_OPEN": score += 1
        return score

    def risk_label(self) -> str:
        s = self.risk_score()
        if s >= 4: return f"{GREEN}LOW{RESET}"
        if s >= 2: return f"{GOLD}MEDIUM{RESET}"
        return f"{RED}HIGH{RESET}"


# ══════════════════════════════════════════════════════════
#  SEED DATA
# ══════════════════════════════════════════════════════════

suppliers = [
    Supplier(1, "Accra Supplies Ltd",    "Medical",     8.0, 7.0, 6.0, 9.0, 320000),
    Supplier(2, "Kumasi Tech Hub",       "IT",          5.0, 6.0, 4.0, 7.0, 210000),
    Supplier(3, "Tema Port Logistics",   "Logistics",   3.0, 4.0, 3.0, 5.0, 180000),
    Supplier(4, "KSTU Medical Stores",   "Medical",     9.0, 8.0, 7.0, 9.0, 150000),
    Supplier(5, "Ashanti Office Hub",    "Office",      7.0, 8.0, 6.0, 8.0,  95000),
    Supplier(6, "Greater Accra Maint.",  "Maintenance", 4.0, 5.0, 4.0, 6.0, 140000),
]

inventory = [
    InventoryItem("Surgical Gloves",  500, 12.50, 2400, 60.0, 2.50, "A"),
    InventoryItem("Hand Sanitizer",   150, 15.00,  800, 35.0, 3.00, "A"),
    InventoryItem("A4 Paper",         200,  8.00, 1200, 40.0, 1.50, "B"),
    InventoryItem("Printer Toner",     50, 85.00,  300, 50.0, 8.00, "B"),
    InventoryItem("Biro Pens",        300,  3.50,  600, 20.0, 0.75, "C"),
    InventoryItem("Latex Gloves",     400, 10.00, 1800, 55.0, 2.00, "A"),
    InventoryItem("Disinfectant",     120, 18.00,  960, 45.0, 3.50, "B"),
    InventoryItem("Face Masks",      1200,  5.00, 3600, 40.0, 1.00, "A"),
]

orders = [
    PurchaseOrder("PO-2026-001", "Accra Supplies Ltd",  "Surgical Gloves (500 boxes)", 500,  12.50, "APPROVED"),
    PurchaseOrder("PO-2026-002", "Kumasi Tech Hub",     "Laptop Computers",              5, 3500.0, "PENDING"),
    PurchaseOrder("PO-2026-003", "Ashanti Office Hub",  "A4 Paper (200 reams)",        200,   8.00, "DELIVERED"),
    PurchaseOrder("PO-2026-004", "Tema Port Logistics", "Freight — Kumasi Route",        1, 45000.0,"APPROVED"),
    PurchaseOrder("PO-2026-005", "KSTU Medical Stores", "Hand Sanitizer (300 units)",  300,  15.00, "PENDING"),
]

tenders = [
    Tender("MOH/2026/047",  "Supply of Surgical Gloves",         125000,  "BID_OPEN",   "RESTRICTED",    "2026-07-05", True),
    Tender("GES/2026/012",  "IT Equipment — Ghana Education",    380000,  "EVALUATION", "NATIONAL",      "2026-08-15", True),
    Tender("KNUST/2026/03", "Office Furniture — KNUST",           55000,  "AWARDED",    "RESTRICTED",    "2026-05-30", True),
    Tender("MOH/2026/051",  "Medical Equipment Maintenance",      28000,  "ADVERTISED", "RFQ",           "2026-07-20", False),
    Tender("GPHA/2026/08",  "Port Logistics Framework — Tema", 6200000,  "BID_OPEN",   "INTERNATIONAL", "2026-09-01", True),
]

# ══════════════════════════════════════════════════════════
#  DATA STRUCTURES DEMO
# ══════════════════════════════════════════════════════════

def data_structures_demo() -> None:
    section("🗂️  DATA STRUCTURES DEMO", "Lists · Dicts · Stack · Queue · Heap · Sets")

    # Stack — LIFO: PO approval queue
    print(f"\n{BOLD}  Stack (LIFO) — PO Approval Process:{RESET}")
    stack = []
    for po in orders:
        if po.status == "PENDING":
            stack.append(po.po_number)
            print(f"  PUSH → {po.po_number}")
    print(f"  Stack contents: {stack}")
    while stack:
        print(f"  POP  ← {stack.pop()} (approving...)")

    # Queue — FIFO: Tender processing
    print(f"\n{BOLD}  Queue (FIFO) — Tender Processing:{RESET}")
    queue: deque = deque()
    for t in tenders:
        queue.append(t.reference)
    print(f"  Queue: {list(queue)}")
    print(f"  Process first: {queue.popleft()}")
    print(f"  Process next:  {queue.popleft()}")

    # Dictionary — Spend by category
    print(f"\n{BOLD}  Dictionary — Spend by Category:{RESET}")
    spend_by_cat: dict[str, float] = {}
    for s in suppliers:
        spend_by_cat[s.category] = spend_by_cat.get(s.category, 0) + s.spend
    max_spend = max(spend_by_cat.values())
    for cat, spend in sorted(spend_by_cat.items(), key=lambda x: -x[1]):
        print(f"  {cat:<16} {bar(spend, max_spend)} {ghs(spend)}")

    # Min-heap — Find lowest scoring suppliers
    print(f"\n{BOLD}  Min-Heap — Top 3 Highest Risk Suppliers:{RESET}")
    heap = [(s.weighted_score(), s.name) for s in suppliers]
    heapq.heapify(heap)
    for _ in range(3):
        score, name = heapq.heappop(heap)
        print(f"  Score {score:.1f} → {name}")

    # Set — Unique categories
    categories = {s.category for s in suppliers}
    print(f"\n{BOLD}  Set — Unique Supplier Categories:{RESET}")
    print(f"  {categories}")


# ══════════════════════════════════════════════════════════
#  SUPPLIER DASHBOARD — Project 3
# ══════════════════════════════════════════════════════════

def supplier_dashboard() -> None:
    section("⚠️  SUPPLIER SCORECARD DASHBOARD", "Project 3 — Weighted KPI · Sorted by Score")

    sorted_suppliers = sorted(suppliers, key=lambda s: s.weighted_score(), reverse=True)

    print(f"\n{BOLD}  {'Supplier':<24} {'Score':<8} {'Spend':<16} Risk{RESET}")
    divider()
    for s in sorted_suppliers:
        score = s.weighted_score()
        print(f"  {s.name:<24} {score:<8.1f} {ghs(s.spend):<16} {s.risk_level()}")

    avg  = sum(s.weighted_score() for s in suppliers) / len(suppliers)
    high = sum(1 for s in suppliers if s.weighted_score() < 4)
    total_spend = sum(s.spend for s in suppliers)
    divider()
    print(f"  Avg Score: {avg:.1f}/10 · Total Spend: {ghs(total_spend)} · High Risk: {high}")


# ══════════════════════════════════════════════════════════
#  INVENTORY & EOQ — Project 4
# ══════════════════════════════════════════════════════════

def inventory_dashboard() -> None:
    section("📦 INVENTORY & EOQ DASHBOARD", "Project 4 — EOQ · Safety Stock · ABC Analysis")

    print(f"\n{BOLD}  {'Item':<18} {'EOQ':>6} {'SafeStk':>8} {'ROP':>6} {'Ann.Value':>14} Class{RESET}")
    divider(60)

    # ABC classification
    items_sorted = sorted(inventory, key=lambda i: i.annual_value(), reverse=True)
    total_val    = sum(i.annual_value() for i in items_sorted)
    cum          = 0
    for item in items_sorted:
        cum += item.annual_value() / total_val * 100
        item.abc_class = "A" if cum <= 70 else "B" if cum <= 90 else "C"

    for item in inventory:
        color = GOLD if item.abc_class == "A" else CYAN if item.abc_class == "B" else DIM
        print(f"  {item.name:<18} {item.eoq():>6.0f} {item.safety_stock():>8.0f} "
              f"{item.reorder_point():>6.0f} {ghs(item.annual_value()):>14} "
              f"{color}{item.abc_class}{RESET}")

    total = sum(i.annual_value() for i in inventory)
    divider(60)
    print(f"{GOLD}{BOLD}  Total Inventory Value: {ghs(total)}{RESET}")

    # ABC summary
    a = [i for i in inventory if i.abc_class == "A"]
    b = [i for i in inventory if i.abc_class == "B"]
    c = [i for i in inventory if i.abc_class == "C"]
    print(f"\n  {GOLD}A: {len(a)} items · {ghs(sum(i.annual_value() for i in a))} · Weekly review{RESET}")
    print(f"  {CYAN}B: {len(b)} items · {ghs(sum(i.annual_value() for i in b))} · Monthly review{RESET}")
    print(f"  {DIM}C: {len(c)} items · {ghs(sum(i.annual_value() for i in c))} · Quarterly review{RESET}")


# ══════════════════════════════════════════════════════════
#  PURCHASE ORDERS — Project 1
# ══════════════════════════════════════════════════════════

def po_dashboard() -> None:
    section("🔃 PURCHASE ORDER DASHBOARD", "Project 1 — P2P Workflow · Acts 663 & 914 Thresholds")

    sorted_pos = sorted(orders, key=lambda po: po.total_value(), reverse=True)

    print(f"\n{BOLD}  {'PO Number':<14} {'Supplier':<24} {'Value':<14} {'Method':<26} Status{RESET}")
    divider(90)
    for po in sorted_pos:
        status_color = GREEN if po.status == "APPROVED" else GOLD if po.status == "PENDING" else CYAN
        print(f"  {po.po_number:<14} {po.supplier:<24} {ghs(po.total_value()):<14} "
              f"{po.ppa_method():<26} {status_color}{po.status}{RESET}")

    total    = sum(po.total_value() for po in orders)
    approved = sum(po.total_value() for po in orders if po.status == "APPROVED")
    divider(90)
    print(f"  Total: {ghs(total)} · Approved: {ghs(approved)}")


# ══════════════════════════════════════════════════════════
#  TENDER TRACKER — Project 7
# ══════════════════════════════════════════════════════════

def tender_dashboard() -> None:
    section("🔒 TENDER RISK DASHBOARD", "Project 7 — Ghana e-GP · Acts 663 & 914 · Risk Rating")

    print(f"\n{BOLD}  {'Reference':<16} {'Title':<34} {'Value':<14} Risk{RESET}")
    divider(75)
    for t in tenders:
        title = t.title[:32] + ".." if len(t.title) > 32 else t.title
        print(f"  {t.reference:<16} {title:<34} {ghs(t.value):<14} {t.risk_label()}")
        print(f"  {'':<16} Stage: {t.stage:<18} Method: {t.method:<18} "
              f"{'✅ Compliant' if t.compliant else '❌ Non-compliant'}\n")


# ══════════════════════════════════════════════════════════
#  SPEND ANALYTICS — Project 5
# ══════════════════════════════════════════════════════════

def spend_analytics() -> None:
    section("📊 SPEND ANALYTICS", "Project 5 — Ghana Procurement Spend Dashboard")

    # Monthly spend data
    monthly_spend = [42000, 38500, 51000, 46000, 55000, 49000,
                     61000, 58000, 67000, 72000, 68000, 75000]
    months        = ["Jan","Feb","Mar","Apr","May","Jun",
                     "Jul","Aug","Sep","Oct","Nov","Dec"]

    print(f"\n{BOLD}  Monthly Spend Trend (GHS):{RESET}")
    max_spend = max(monthly_spend)
    for i, (m, s) in enumerate(zip(months, monthly_spend)):
        b = bar(s, max_spend, 20)
        print(f"  {m} {GOLD}{b}{RESET} {ghs(s)}")

    # Statistics
    mean   = sum(monthly_spend) / len(monthly_spend)
    variance = sum((x - mean) ** 2 for x in monthly_spend) / len(monthly_spend)
    std    = math.sqrt(variance)
    growth = ((monthly_spend[-1] - monthly_spend[0]) / monthly_spend[0]) * 100

    print(f"\n{BOLD}  Statistics:{RESET}")
    print(f"  Total Annual:  {ghs(sum(monthly_spend))}")
    print(f"  Mean Monthly:  {ghs(mean)}")
    print(f"  Std Deviation: {ghs(std)}")
    print(f"  YTD Growth:    {growth:.1f}%")

    # Simple linear regression forecast
    n    = len(monthly_spend)
    x    = list(range(1, n + 1))
    x_mean = sum(x) / n
    y_mean = mean
    slope  = sum((xi - x_mean) * (yi - y_mean)
                 for xi, yi in zip(x, monthly_spend)) / \
             sum((xi - x_mean) ** 2 for xi in x)
    intercept = y_mean - slope * x_mean

    print(f"\n{BOLD}  Forecast (next 3 months):{RESET}")
    for i in range(13, 16):
        forecast = intercept + slope * i
        m_name   = months[(i - 1) % 12]
        print(f"  → {m_name} 2027: {ghs(forecast)}")


# ══════════════════════════════════════════════════════════
#  MAIN MENU
# ══════════════════════════════════════════════════════════

def print_banner() -> None:
    print(f"\n{GOLD}{BOLD}")
    print("  ╔══════════════════════════════════════════════════════╗")
    print("  ║    GHANA PROCUREMENT ANALYTICS — Python  v1.0      ║")
    print("  ║    Frank Oduro · KSTU · Kumasi, Ghana 🇬🇭           ║")
    print("  ║    OOP · Data Structures · Analytics · 7 Projects   ║")
    print("  ╚══════════════════════════════════════════════════════╝")
    print(f"{RESET}{DIM}  github.com/Ofrank-design · ofrank-design.github.io\n{RESET}")

def main() -> None:
    print_banner()
    while True:
        print(f"{CYAN}{BOLD}\n  ══ MAIN MENU ══════════════════════════════{RESET}")
        print(f"{GOLD}  [1]{WHITE} Data Structures Demo   {DIM}→ Stack · Queue · Heap · Dict{RESET}")
        print(f"{GOLD}  [2]{WHITE} Supplier Dashboard     {DIM}→ Project 3{RESET}")
        print(f"{GOLD}  [3]{WHITE} Inventory & EOQ        {DIM}→ Project 4{RESET}")
        print(f"{GOLD}  [4]{WHITE} Purchase Orders        {DIM}→ Project 1{RESET}")
        print(f"{GOLD}  [5]{WHITE} Tender Risk Tracker    {DIM}→ Project 7{RESET}")
        print(f"{GOLD}  [6]{WHITE} Spend Analytics        {DIM}→ Project 5{RESET}")
        print(f"{RED}  [0]{WHITE} Exit{RESET}")
        print(f"{CYAN}  ════════════════════════════════════════════{RESET}")
        choice = input(f"{GOLD}  Select › {RESET}").strip()

        if   choice == "1": data_structures_demo()
        elif choice == "2": supplier_dashboard()
        elif choice == "3": inventory_dashboard()
        elif choice == "4": po_dashboard()
        elif choice == "5": tender_dashboard()
        elif choice == "6": spend_analytics()
        elif choice == "0":
            print(f"{GOLD}{BOLD}\n  Goodbye · Frank Oduro · KSTU · Ghana 🇬🇭\n{RESET}")
            break
        else:
            print(f"{RED}  ✗ Invalid option.{RESET}")

if __name__ == "__main__":
    main()
