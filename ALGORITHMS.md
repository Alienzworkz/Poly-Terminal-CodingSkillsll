# Algorithms Documentation

This document explains the algorithms implemented in the Decentralized Trading Terminal.

## 1. Greedy Algorithms

### 1.1 Best Execution Price Selection

**Purpose**: Find the optimal average execution price when buying or selling a large order across multiple price levels.

**Algorithm**:
```
Input: prices[], quantities[], targetQuantity, isBuy
Output: averageExecutionPrice

1. Create price-quantity pairs
2. Sort by price:
   - Ascending if buying (cheapest first)
   - Descending if selling (highest first)
3. Greedily take from best prices until target quantity is met
4. Calculate weighted average execution price
```

**Time Complexity**: O(n log n) due to sorting
**Space Complexity**: O(n)

**Example**:
```
Buy 500 shares with available levels:
- $100.20 x 300 shares
- $100.30 x 200 shares
- $100.50 x 100 shares

Greedy selection:
- Take 300 @ $100.20 = $30,060
- Take 200 @ $100.30 = $20,060
Total: $50,120 / 500 = $100.24 average
```

### 1.2 Order Splitting for Minimal Market Impact

**Purpose**: Split a large order across multiple price levels to minimize market impact.

**Algorithm**:
```
Input: orderBookLevels[], totalQuantity, isBuy
Output: splits[] (price, quantity pairs)

1. For each level in order book (best price first):
   2. Take min(remainingQty, levelQuantity)
   3. Add to splits
   4. Update remainingQty
5. Return splits
```

**Time Complexity**: O(n)
**Space Complexity**: O(n)

## 2. Dynamic Programming Algorithms

### 2.1 Portfolio Optimization (Knapsack Variant)

**Purpose**: Maximize expected returns given a budget constraint.

**Algorithm**:
```
Input: symbols[], prices[], expectedReturns[], budget
Output: allocation map

1. Create DP table: dp[i][w] = max return with first i items and budget w
2. For each item i:
   3. For each budget w:
      4. Option 1: Don't take item i
         dp[i][w] = dp[i-1][w]
      5. Option 2: Take item i (can take multiple)
         if w >= price[i]:
            dp[i][w] = max(dp[i][w], dp[i][w-price[i]] + return[i])
6. Backtrack to find allocation
```

**Time Complexity**: O(n × W) where W is budget
**Space Complexity**: O(n × W)

**Example**:
```
Budget: $10,000
Stocks:
- AAPL: $150, return 15%
- GOOGL: $2800, return 20%
- MSFT: $300, return 12%

DP finds optimal mix:
- AAPL: 20 shares ($3,000)
- GOOGL: 2 shares ($5,600)
- MSFT: 4 shares ($1,200)
Total: $9,800 invested
```

### 2.2 Optimal Trade Sequencing

**Purpose**: Minimize total cost when executing a sequence of trades.

**Algorithm**:
```
Input: prices[], quantities[], maxTrades
Output: optimal sequence of trade indices

1. Create DP table: dp[i][k] = min cost for first i trades using k executions
2. For each trade i:
   3. For each execution count k:
      4. Option 1: Skip this trade
         dp[i][k] = dp[i-1][k]
      5. Option 2: Execute this trade
         dp[i][k] = min(dp[i][k], dp[i-1][k-1] + cost[i])
6. Backtrack to find sequence
```

**Time Complexity**: O(n × k) where k is max trades
**Space Complexity**: O(n × k)

### 2.3 Risk-Adjusted Portfolio Allocation

**Purpose**: Allocate portfolio weights based on risk-return tradeoff.

**Algorithm**:
```
Input: symbols[], expectedReturns[], risks[], riskTolerance
Output: allocation weights (sum to 1.0)

1. Calculate Sharpe-like ratio for each asset:
   ratio[i] = expectedReturn[i] / risk[i]
2. Sort by ratio (descending)
3. Allocate weights proportional to risk-adjusted returns
4. Normalize weights to sum to 1.0
```

**Time Complexity**: O(n log n)
**Space Complexity**: O(n)

## 3. Order Matching Algorithm

**Purpose**: Match buy and sell orders based on price-time priority.

**Algorithm**:
```
Input: buyOrders (max heap), sellOrders (min heap)
Output: executed trades[]

1. While both heaps are non-empty:
   2. Get best bid (highest buy price)
   3. Get best ask (lowest sell price)
   4. If bid >= ask:
      5. Match orders at ask price (price-time priority)
      6. Execute trade for min(buyQty, sellQty)
      7. Update or remove orders
      8. Add trade to blockchain
   9. Else: break (no more matches)
```

**Time Complexity**: O(m log n) where m is matches, n is orders
**Space Complexity**: O(n)

## 4. Blockchain Mining

**Purpose**: Create immutable record of trades using proof-of-work.

**Algorithm**:
```
Input: pendingTrades[], previousHash, difficulty
Output: new block with valid hash

1. Create block with trades and previous hash
2. Set nonce = 0
3. While hash doesn't start with 'difficulty' zeros:
   4. Increment nonce
   5. Recalculate hash = SHA256(block data + nonce)
6. Add block to chain
```

**Time Complexity**: O(2^difficulty) expected
**Space Complexity**: O(1)

## Algorithm Comparison

| Algorithm | Type | Time Complexity | Use Case |
|-----------|------|-----------------|----------|
| Best Execution | Greedy | O(n log n) | Order execution |
| Order Splitting | Greedy | O(n) | Market impact |
| Portfolio Opt | DP | O(n × W) | Asset allocation |
| Trade Sequence | DP | O(n × k) | Execution planning |
| Risk Allocation | Greedy | O(n log n) | Risk management |
| Order Matching | Heap | O(m log n) | Trade execution |

## Performance Considerations

1. **Greedy algorithms** are fast and work well for local optimization
2. **DP algorithms** provide global optimality but require more computation
3. **Blockchain mining** is intentionally slow for security
4. **Order matching** uses heaps for O(log n) insertions and deletions

## Future Enhancements

- Machine learning for price prediction
- Multi-objective optimization (return, risk, liquidity)
- Advanced order types (iceberg, TWAP, VWAP)
- Cross-chain trading support
