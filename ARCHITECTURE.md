# System Architecture

## High-Level Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    TERMINAL UI LAYER                         │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐   │
│  │  Market  │  │  Order   │  │Portfolio │  │Blockchain│   │
│  │   Data   │  │   Book   │  │  View    │  │ Explorer │   │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘   │
└─────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────┐
│                   BUSINESS LOGIC LAYER                       │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐     │
│  │   Trading    │  │   Algorithm  │  │  Portfolio   │     │
│  │  Algorithms  │  │   Engine     │  │   Manager    │     │
│  └──────────────┘  └──────────────┘  └──────────────┘     │
└─────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────┐
│                     DATA LAYER                               │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐     │
│  │  Order Book  │  │  Blockchain  │  │  Portfolio   │     │
│  │   (Heaps)    │  │   (Chain)    │  │  (HashMap)   │     │
│  └──────────────┘  └──────────────┘  └──────────────┘     │
└─────────────────────────────────────────────────────────────┘
```

## Component Diagram

```
┌─────────────────────────────────────────────────────────────┐
│                        main.cpp                              │
│                     (Entry Point)                            │
└────────────┬────────────────────────────────────────────────┘
             │
             ├──────────────┬──────────────┬──────────────┐
             ▼              ▼              ▼              ▼
    ┌────────────┐  ┌────────────┐  ┌────────────┐  ┌────────────┐
    │ Terminal   │  │  Market    │  │ Blockchain │  │ Portfolio  │
    │    UI      │  │ (OrderBook)│  │            │  │            │
    └────────────┘  └────────────┘  └────────────┘  └────────────┘
         │                │                │                │
         │                ▼                │                │
         │         ┌────────────┐          │                │
         │         │  Trading   │          │                │
         │         │ Algorithms │          │                │
         │         └────────────┘          │                │
         │                │                │                │
         └────────────────┴────────────────┴────────────────┘
```

## Data Flow Diagram

### Order Placement Flow

```
User Input
    │
    ▼
┌─────────────┐
│ Terminal UI │
└──────┬──────┘
       │ 1. Place Order
       ▼
┌─────────────┐
│ Order Book  │
└──────┬──────┘
       │ 2. Add to Queue
       ▼
┌─────────────┐
│   Matching  │ ◄─── Greedy Algorithm
│   Engine    │      (Best Execution)
└──────┬──────┘
       │ 3. Execute Trade
       ▼
┌─────────────┐
│  Blockchain │ ◄─── Proof-of-Work
│   Mining    │      (SHA-256)
└──────┬──────┘
       │ 4. Record Trade
       ▼
┌─────────────┐
│  Portfolio  │
│   Update    │
└─────────────┘
```

### Algorithm Execution Flow

```
Market Data
    │
    ▼
┌──────────────────┐
│ Greedy Algorithm │
├──────────────────┤
│ • Sort by price  │
│ • Select best    │
│ • Calculate avg  │
└────────┬─────────┘
         │
         ▼
    Execution
    Decision
         │
         ▼
┌──────────────────┐
│   DP Algorithm   │
├──────────────────┤
│ • Build DP table │
│ • Find optimal   │
│ • Backtrack      │
└────────┬─────────┘
         │
         ▼
    Portfolio
    Allocation
```

## Class Diagram

```
┌─────────────────────────────────────────────────────────────┐
│                        TerminalUI                            │
├─────────────────────────────────────────────────────────────┤
│ - market: Market*                                            │
│ - blockchain: Blockchain*                                    │
│ - portfolio: Portfolio*                                      │
├─────────────────────────────────────────────────────────────┤
│ + displayMainScreen()                                        │
│ + handleUserInput()                                          │
│ + run()                                                      │
└─────────────────────────────────────────────────────────────┘
                            │
                            │ uses
                            ▼
┌─────────────────────────────────────────────────────────────┐
│                          Market                              │
├─────────────────────────────────────────────────────────────┤
│ - orderBooks: map<string, OrderBook*>                        │
├─────────────────────────────────────────────────────────────┤
│ + addSymbol(symbol)                                          │
│ + getOrderBook(symbol): OrderBook*                           │
│ + displayMarket()                                            │
└─────────────────────────────────────────────────────────────┘
                            │
                            │ contains
                            ▼
┌─────────────────────────────────────────────────────────────┐
│                        OrderBook                             │
├─────────────────────────────────────────────────────────────┤
│ - buyOrders: priority_queue<Order>  (max heap)              │
│ - sellOrders: priority_queue<Order> (min heap)              │
│ - allOrders: map<int, Order>                                 │
├─────────────────────────────────────────────────────────────┤
│ + addOrder(price, qty, side): int                            │
│ + matchOrders(): vector<Trade>                               │
│ + getBestBid(): double                                       │
│ + getBestAsk(): double                                       │
└─────────────────────────────────────────────────────────────┘
                            │
                            │ produces
                            ▼
┌─────────────────────────────────────────────────────────────┐
│                        Blockchain                            │
├─────────────────────────────────────────────────────────────┤
│ - chain: vector<Block>                                       │
│ - pendingTrades: vector<Trade>                               │
│ - difficulty: int                                            │
├─────────────────────────────────────────────────────────────┤
│ + addTrade(trade)                                            │
│ + minePendingTrades()                                        │
│ + isChainValid(): bool                                       │
└─────────────────────────────────────────────────────────────┘
                            │
                            │ contains
                            ▼
┌─────────────────────────────────────────────────────────────┐
│                          Block                               │
├─────────────────────────────────────────────────────────────┤
│ - index: int                                                 │
│ - timestamp: time_t                                          │
│ - trades: vector<Trade>                                      │
│ - previousHash: string                                       │
│ - hash: string                                               │
│ - nonce: int                                                 │
├─────────────────────────────────────────────────────────────┤
│ + mineBlock(difficulty)                                      │
│ + calculateHash(): string                                    │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│                  GreedyExecutionAlgorithm                    │
├─────────────────────────────────────────────────────────────┤
│ + findBestExecutionPrice(...): double                        │
│ + splitOrder(...): vector<pair<double, int>>                 │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│               DynamicProgrammingAlgorithm                    │
├─────────────────────────────────────────────────────────────┤
│ + optimizePortfolio(...): map<string, int>                   │
│ + optimalTradeSequence(...): vector<int>                     │
│ + riskAdjustedAllocation(...): map<string, double>           │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│                        Portfolio                             │
├─────────────────────────────────────────────────────────────┤
│ - positions: map<string, Position>                           │
│ - cash: double                                               │
├─────────────────────────────────────────────────────────────┤
│ + addPosition(symbol, qty, price)                            │
│ + updatePrice(symbol, price)                                 │
│ + getTotalValue(): double                                    │
│ + getTotalPnL(): double                                      │
└─────────────────────────────────────────────────────────────┘
```

## Algorithm Flow Diagrams

### Greedy Algorithm: Best Execution

```
START
  │
  ▼
Input: prices[], quantities[], targetQty
  │
  ▼
Create price-quantity pairs
  │
  ▼
Sort by price (ascending for buy)
  │
  ▼
Initialize: totalCost = 0, remaining = targetQty
  │
  ▼
┌─────────────────────┐
│ For each price level│
└──────────┬──────────┘
           │
           ▼
    ┌──────────────┐
    │ remaining > 0?│
    └──────┬───────┘
           │ Yes
           ▼
    Take min(remaining, available)
           │
           ▼
    Update totalCost
           │
           ▼
    Update remaining
           │
           └──────┐
                  │
                  ▼ No
           Calculate average
                  │
                  ▼
                RETURN
```

### Dynamic Programming: Portfolio Optimization

```
START
  │
  ▼
Input: symbols[], prices[], returns[], budget
  │
  ▼
Create DP table: dp[n+1][W+1]
  │
  ▼
Initialize: dp[0][w] = 0 for all w
  │
  ▼
┌─────────────────────────┐
│ For each item i (1 to n)│
└──────────┬──────────────┘
           │
           ▼
    ┌──────────────────────┐
    │ For each budget w    │
    └──────────┬───────────┘
               │
               ▼
        ┌──────────────┐
        │ Don't take i │
        │ dp[i][w] =   │
        │ dp[i-1][w]   │
        └──────┬───────┘
               │
               ▼
        ┌──────────────┐
        │ w >= price[i]?│
        └──────┬───────┘
               │ Yes
               ▼
        ┌──────────────┐
        │   Take i     │
        │ dp[i][w] =   │
        │ max(...)     │
        └──────┬───────┘
               │
               └──────┐
                      │
                      ▼
               Backtrack to find allocation
                      │
                      ▼
                   RETURN
```

### Order Matching Algorithm

```
START
  │
  ▼
Input: buyOrders (max heap), sellOrders (min heap)
  │
  ▼
Initialize: executedTrades = []
  │
  ▼
┌─────────────────────────────┐
│ While both heaps non-empty  │
└──────────┬──────────────────┘
           │
           ▼
    Get topBuy (highest bid)
           │
           ▼
    Get topSell (lowest ask)
           │
           ▼
    ┌──────────────┐
    │ bid >= ask?  │
    └──────┬───────┘
           │ Yes
           ▼
    matchQty = min(buyQty, sellQty)
           │
           ▼
    executionPrice = ask (price-time priority)
           │
           ▼
    Create Trade record
           │
           ▼
    Update order quantities
           │
           ▼
    Remove filled orders
           │
           └──────┐
                  │
                  ▼ No
           RETURN executedTrades
```

## Blockchain Structure

```
Genesis Block (Block 0)
┌─────────────────────────┐
│ Index: 0                │
│ Timestamp: ...          │
│ Trades: []              │
│ Previous Hash: "0"      │
│ Hash: abc123...         │
│ Nonce: 0                │
└────────────┬────────────┘
             │
             ▼
        Block 1
┌─────────────────────────┐
│ Index: 1                │
│ Timestamp: ...          │
│ Trades: [Trade1, ...]   │
│ Previous Hash: abc123...│
│ Hash: def456...         │
│ Nonce: 1247             │
└────────────┬────────────┘
             │
             ▼
        Block 2
┌─────────────────────────┐
│ Index: 2                │
│ Timestamp: ...          │
│ Trades: [Trade2, ...]   │
│ Previous Hash: def456...│
│ Hash: ghi789...         │
│ Nonce: 2891             │
└─────────────────────────┘
```

## Memory Layout

```
Order Book Memory Structure:
┌─────────────────────────────────────┐
│         Buy Orders (Max Heap)       │
│  ┌───────┐  ┌───────┐  ┌───────┐  │
│  │$150.10│  │$150.05│  │$150.00│  │
│  └───────┘  └───────┘  └───────┘  │
└─────────────────────────────────────┘
┌─────────────────────────────────────┐
│        Sell Orders (Min Heap)       │
│  ┌───────┐  ┌───────┐  ┌───────┐  │
│  │$150.15│  │$150.20│  │$150.25│  │
│  └───────┘  └───────┘  └───────┘  │
└─────────────────────────────────────┘
┌─────────────────────────────────────┐
│      All Orders (Hash Map)          │
│  ID → Order mapping for O(1) lookup │
└─────────────────────────────────────┘
```

## Performance Characteristics

```
Operation Performance:
┌────────────────────┬──────────────┬──────────────┐
│    Operation       │ Time         │ Space        │
├────────────────────┼──────────────┼──────────────┤
│ Add Order          │ O(log n)     │ O(1)         │
│ Match Orders       │ O(m log n)   │ O(m)         │
│ Get Best Bid/Ask   │ O(1)         │ O(1)         │
│ Greedy Execution   │ O(n log n)   │ O(n)         │
│ DP Portfolio Opt   │ O(n × W)     │ O(n × W)     │
│ Mine Block         │ O(2^d)       │ O(1)         │
│ Validate Chain     │ O(b × t)     │ O(1)         │
└────────────────────┴──────────────┴──────────────┘

Where:
  n = number of orders
  m = number of matches
  W = budget amount
  d = difficulty level
  b = number of blocks
  t = trades per block
```

## Deployment Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    User's Terminal                           │
│  ┌────────────────────────────────────────────────────┐    │
│  │              Trading Terminal Process               │    │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────┐         │    │
│  │  │   UI     │  │  Logic   │  │   Data   │         │    │
│  │  └──────────┘  └──────────┘  └──────────┘         │    │
│  └────────────────────────────────────────────────────┘    │
│                          │                                   │
│                          ▼                                   │
│  ┌────────────────────────────────────────────────────┐    │
│  │              OpenSSL Library                        │    │
│  │         (SHA-256 Hashing for Blockchain)            │    │
│  └────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
```

---

This architecture demonstrates:
- Modular design with clear separation of concerns
- Efficient data structures for performance
- Algorithm integration at multiple layers
- Blockchain for immutability and transparency
- Clean interfaces between components
