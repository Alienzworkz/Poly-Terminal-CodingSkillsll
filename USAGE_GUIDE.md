# Usage Guide

## Getting Started

After building and running the terminal, you'll see the main interface with market data and a menu.

## Main Menu Options

### 1. View Market Data
Displays current bid/ask prices for all available symbols:
- **Bid**: Highest price buyers are willing to pay
- **Ask**: Lowest price sellers are willing to accept
- **Spread**: Difference between ask and bid
- **Last**: Most recent trade price

### 2. View Order Book
Shows the depth of market for a specific symbol:
```
Enter symbol: AAPL
```

You'll see:
- **Asks (Sell Orders)**: Sorted by price (lowest first)
- **Bids (Buy Orders)**: Sorted by price (highest first)
- **Spread**: Current bid-ask spread

### 3. Place Order
Submit a new buy or sell order:
```
Enter symbol: AAPL
Enter side (BUY/SELL): BUY
Enter price: 150.00
Enter quantity: 100
Enter trader name: Trader1
```

The system will:
1. Add your order to the order book
2. Attempt to match with existing orders
3. Execute trades if matches are found
4. Record trades to the blockchain
5. Update your portfolio

### 4. View Portfolio
Shows your current positions:
- Symbol and quantity held
- Average purchase price
- Current market price
- Unrealized P&L (profit/loss)
- Total portfolio value
- Available cash

### 5. View Blockchain
Displays the complete blockchain:
- All mined blocks
- Trades in each block
- Block hashes and timestamps
- Chain validation status

### 6. Mine Pending Trades
Mines pending trades into a new block:
- Uses proof-of-work (difficulty level 2)
- Creates immutable record
- Links to previous block
- Validates entire chain

### 7. Run Greedy Algorithm Demo
Demonstrates the greedy algorithm for best execution:
- Given multiple price levels
- Finds optimal average execution price
- Shows how to minimize trading costs

### 8. Run DP Portfolio Optimization
Demonstrates dynamic programming for portfolio allocation:
- Given a budget constraint
- Maximizes expected returns
- Shows optimal number of shares for each symbol

## Trading Strategies

### Market Making
Place both buy and sell orders to capture the spread:
```
1. Place BUY order at $149.90
2. Place SELL order at $150.10
3. Profit from the $0.20 spread when both execute
```

### Momentum Trading
Use the greedy algorithm to identify trends:
- Algorithm analyzes recent price history
- Generates BUY/SELL/HOLD signals
- Execute trades based on signals

### Portfolio Optimization
Use DP algorithm to optimize holdings:
1. View current portfolio
2. Run DP optimization with your budget
3. Place orders to rebalance to optimal allocation

## Algorithm Examples

### Greedy Algorithm: Best Execution
**Problem**: You want to buy 500 shares. Multiple price levels available.

**Solution**: Greedy algorithm selects from cheapest levels first:
```
Available:
- 300 shares @ $100.20
- 200 shares @ $100.30
- 150 shares @ $100.50

Greedy selection:
- Take 300 @ $100.20 = $30,060
- Take 200 @ $100.30 = $20,060
Total: $50,120 / 500 = $100.24 average
```

### Dynamic Programming: Portfolio Optimization
**Problem**: Allocate $10,000 across multiple stocks to maximize returns.

**Solution**: DP algorithm solves knapsack variant:
```
Stocks:
- AAPL: $150, 15% return
- GOOGL: $2800, 20% return
- MSFT: $300, 12% return

Optimal allocation:
- AAPL: 20 shares ($3,000)
- GOOGL: 2 shares ($5,600)
- MSFT: 4 shares ($1,200)
Total invested: $9,800
```

## Blockchain Features

### Trade Recording
Every executed trade is recorded:
1. Trade details (symbol, price, quantity, parties)
2. Added to pending trades pool
3. Mined into a block
4. Permanently stored in blockchain

### Block Mining
Mining process:
1. Collect pending trades
2. Create new block with previous hash
3. Find nonce that produces valid hash (starts with '00')
4. Add block to chain
5. Clear pending trades

### Chain Validation
The system validates:
- Each block's hash is correct
- Each block links to previous block
- No tampering has occurred

## Tips and Best Practices

1. **Start Small**: Place small orders first to understand the system
2. **Check Order Book**: View order book before placing orders
3. **Mine Regularly**: Mine pending trades to keep blockchain updated
4. **Monitor Portfolio**: Track your positions and P&L
5. **Use Algorithms**: Leverage greedy and DP algorithms for better decisions

## Example Trading Session

```
1. View Market Data
   - See AAPL bid: $150.00, ask: $150.10

2. Place Buy Order
   - Symbol: AAPL
   - Side: BUY
   - Price: $150.05
   - Quantity: 50
   - Trader: MyAccount

3. Order Matches!
   - Executed 50 @ $150.05
   - Trade added to pending

4. Mine Pending Trades
   - Block mined successfully
   - Trade now in blockchain

5. View Portfolio
   - AAPL: 50 shares @ $150.05
   - Current price: $150.10
   - P&L: +$2.50

6. Run DP Optimization
   - Suggests optimal allocation
   - Rebalance if needed
```

## Advanced Features

### Order Matching Algorithm
- **Price-Time Priority**: Best prices matched first, then by timestamp
- **Automatic Execution**: Matches happen immediately when possible
- **Partial Fills**: Large orders can be partially filled

### Risk Management
- **Position Limits**: Monitor position sizes
- **Stop Losses**: Manually close positions if needed
- **Diversification**: Use DP algorithm for optimal diversification

### Performance Tracking
- **Unrealized P&L**: Mark-to-market on open positions
- **Total Return**: Compare to initial capital
- **Trade History**: View all trades in blockchain

## Troubleshooting

**Order not matching?**
- Check if your price crosses the spread
- Buy price must be >= best ask
- Sell price must be <= best bid

**Blockchain not updating?**
- Remember to mine pending trades (option 6)
- Mining takes a few seconds due to proof-of-work

**Portfolio not showing trades?**
- Make sure you used the same trader name
- Check if trade was executed (not just placed)

## Next Steps

1. Experiment with different trading strategies
2. Try to profit from the bid-ask spread
3. Use algorithms to optimize your portfolio
4. Build up a trading history in the blockchain
5. Track your performance over time

Happy Trading! 🚀
