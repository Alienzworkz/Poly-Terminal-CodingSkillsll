# Quick Start Guide

Get up and running with the Decentralized Trading Terminal in 5 minutes!

## Step 1: Install Dependencies

### Windows
1. Install MinGW-w64: https://www.mingw-w64.org/
2. Install OpenSSL: https://slproweb.com/products/Win32OpenSSL.html
3. Add both to your PATH

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential libssl-dev
```

### macOS
```bash
xcode-select --install
brew install openssl
```

## Step 2: Build the Project

### Windows
```bash
build.bat
```

### Linux/Mac
```bash
chmod +x build.sh
./build.sh
```

## Step 3: Run the Terminal

### Windows
```bash
trading_terminal.exe
```

### Linux/Mac
```bash
./trading_terminal
```

## Step 4: Explore the Features

### Watch Algorithm Demonstrations
The terminal will automatically show:
1. Greedy algorithm for best execution
2. Dynamic programming for portfolio optimization
3. Risk-adjusted allocation

Press Enter to continue to the main terminal.

### Main Menu Options

```
1. View Market Data       - See live prices
2. View Order Book        - See depth of market
3. Place Order           - Submit buy/sell orders
4. View Portfolio        - Check your positions
5. View Blockchain       - See trade history
6. Mine Pending Trades   - Add trades to blockchain
7. Run Greedy Demo       - Algorithm demonstration
8. Run DP Demo           - Portfolio optimization
9. Exit                  - Close terminal
```

## Step 5: Try Your First Trade

1. **View Market Data** (Option 1)
   - See current prices for AAPL, GOOGL, MSFT, AMZN, TSLA

2. **View Order Book** (Option 2)
   - Enter symbol: `AAPL`
   - See buy and sell orders

3. **Place an Order** (Option 3)
   ```
   Enter symbol: AAPL
   Enter side (BUY/SELL): BUY
   Enter price: 150.05
   Enter quantity: 100
   Enter trader name: MyAccount
   ```

4. **View Portfolio** (Option 4)
   - See your new position
   - Check P&L

5. **Mine Trades** (Option 6)
   - Record trades to blockchain
   - Wait for mining to complete

6. **View Blockchain** (Option 5)
   - See your trade permanently recorded

## Example Session

```
========================================
  ALGORITHM DEMONSTRATIONS
========================================

1. GREEDY ALGORITHM - Best Execution Price
   Finding optimal execution for 500 shares...
   Best BUY execution: $100.24
   Best SELL execution: $100.56

2. DYNAMIC PROGRAMMING - Portfolio Optimization
   Optimizing portfolio with $10,000 budget...
   Optimal allocation:
   - AAPL: 20 shares ($3,000)
   - GOOGL: 2 shares ($5,600)
   - MSFT: 4 shares ($1,200)
   Total invested: $9,800

Press Enter to continue...

========================================
  DECENTRALIZED TRADING TERMINAL
========================================

=== MARKET DATA ===
Symbol      Bid         Ask         Spread      Last
------------------------------------------------------------
AAPL        $150.00     $150.10     $0.10       $150.05
GOOGL       $2800.00    $2801.00    $1.00       $2800.50
MSFT        $300.00     $300.10     $0.10       $300.05
AMZN        $3300.00    $3301.00    $1.00       $3300.50
TSLA        $700.00     $700.20     $0.20       $700.10

=== MENU ===
1. View Market Data
2. View Order Book
3. Place Order
4. View Portfolio
5. View Blockchain
6. Mine Pending Trades
7. Run Greedy Algorithm Demo
8. Run DP Portfolio Optimization
9. Exit

Choice: 3

Enter symbol: AAPL
Enter side (BUY/SELL): BUY
Enter price: 150.05
Enter quantity: 100
Enter trader name: Trader1
Order placed! ID: 7
Trade executed: 100 @ $150.05

Choice: 4

=== PORTFOLIO ===
Cash: $85,005.00
Total Value: $100,005.00
Total P&L: $5.00

Positions:
Symbol    Qty       Avg Price   Curr Price  P&L
------------------------------------------------------------
AAPL      100       $150.00     $150.05     $5.00

Choice: 6

Mining pending trades...
Block mined: 00a3f5d8c9b2e1f4a7d6c5b4a3f2e1d0...
Block mined successfully!

Choice: 5

=== BLOCKCHAIN ===
Total Blocks: 2
Chain Valid: YES

=== Block #1 ===
Timestamp: Mon Apr 27 10:30:45 2026
Hash: 00a3f5d8c9b2e1f4a7d6c5b4a3f2e1d0...
Previous Hash: 0
Nonce: 1247
Trades in block: 1
  Trade 1: AAPL | 100 @ $150.05 | Trader1 <- MarketMaker1
```

## Tips for Success

1. **Start with small orders** to understand the system
2. **Check the order book** before placing orders
3. **Mine regularly** to keep blockchain updated
4. **Use the demos** to learn about algorithms
5. **Monitor your portfolio** to track performance

## Common Commands

| Action | Menu Option | Description |
|--------|-------------|-------------|
| View prices | 1 | See all market data |
| Check depth | 2 | View order book |
| Trade | 3 | Place buy/sell order |
| Check P&L | 4 | View portfolio |
| See history | 5 | View blockchain |
| Record trades | 6 | Mine pending trades |
| Learn greedy | 7 | Algorithm demo |
| Learn DP | 8 | Optimization demo |

## Troubleshooting

**Build fails?**
- Check that g++ is installed: `g++ --version`
- Check that OpenSSL is installed
- See SETUP.md for detailed instructions

**Order not matching?**
- Your buy price must be >= best ask
- Your sell price must be <= best bid
- Check the order book first

**Blockchain not updating?**
- Remember to mine pending trades (option 6)
- Mining takes a few seconds

## Next Steps

1. ✅ Complete your first trade
2. ✅ Mine it to the blockchain
3. ✅ Try the algorithm demos
4. ✅ Optimize your portfolio
5. ✅ Build a trading strategy

## Need Help?

- **Setup issues**: See [SETUP.md](SETUP.md)
- **Usage questions**: See [USAGE_GUIDE.md](USAGE_GUIDE.md)
- **Algorithm details**: See [ALGORITHMS.md](ALGORITHMS.md)
- **Full documentation**: See [PROJECT_REPORT.md](PROJECT_REPORT.md)

---

**Ready to trade? Run the terminal and start exploring!** 🚀
