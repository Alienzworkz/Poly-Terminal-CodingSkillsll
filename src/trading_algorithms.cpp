#include "../include/trading_algorithms.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>

// Greedy Algorithm Implementation
double GreedyExecutionAlgorithm::findBestExecutionPrice(
    const std::vector<double>& prices, 
    const std::vector<int>& quantities,
    int targetQuantity,
    bool isBuy) {
    
    // Greedy approach: select best price levels until target quantity is met
    std::vector<std::pair<double, int>> priceQtyPairs;
    for (size_t i = 0; i < prices.size(); i++) {
        priceQtyPairs.push_back({prices[i], quantities[i]});
    }
    
    // Sort by price (ascending for buy, descending for sell)
    if (isBuy) {
        std::sort(priceQtyPairs.begin(), priceQtyPairs.end());
    } else {
        std::sort(priceQtyPairs.begin(), priceQtyPairs.end(), 
                 [](const auto& a, const auto& b) { return a.first > b.first; });
    }
    
    double totalCost = 0.0;
    int remainingQty = targetQuantity;
    
    for (const auto& pair : priceQtyPairs) {
        int qtyToTake = std::min(remainingQty, pair.second);
        totalCost += qtyToTake * pair.first;
        remainingQty -= qtyToTake;
        
        if (remainingQty == 0) break;
    }
    
    return totalCost / targetQuantity; // Average execution price
}

std::vector<std::pair<double, int>> GreedyExecutionAlgorithm::splitOrder(
    const std::vector<std::pair<double, int>>& orderBookLevels,
    int totalQuantity,
    bool isBuy) {
    
    std::vector<std::pair<double, int>> splits;
    int remainingQty = totalQuantity;
    
    // Greedy: take from best price levels first
    for (const auto& level : orderBookLevels) {
        if (remainingQty == 0) break;
        
        int qtyToTake = std::min(remainingQty, level.second);
        splits.push_back({level.first, qtyToTake});
        remainingQty -= qtyToTake;
    }
    
    return splits;
}

// Dynamic Programming Implementation
std::map<std::string, int> DynamicProgrammingAlgorithm::optimizePortfolio(
    const std::vector<std::string>& symbols,
    const std::vector<double>& prices,
    const std::vector<double>& expectedReturns,
    double budget) {
    
    int n = symbols.size();
    int W = static_cast<int>(budget);
    
    // DP table: dp[i][w] = max expected return with first i items and budget w
    std::vector<std::vector<double>> dp(n + 1, std::vector<double>(W + 1, 0.0));
    std::vector<std::vector<int>> count(n + 1, std::vector<int>(W + 1, 0));
    
    // Fill DP table (0/1 Knapsack variant)
    for (int i = 1; i <= n; i++) {
        int price = static_cast<int>(prices[i-1]);
        double returnVal = expectedReturns[i-1];
        
        for (int w = 0; w <= W; w++) {
            // Don't take item i
            dp[i][w] = dp[i-1][w];
            count[i][w] = count[i-1][w];
            
            // Take item i (can take multiple units)
            if (w >= price) {
                double newReturn = dp[i][w - price] + returnVal;
                if (newReturn > dp[i][w]) {
                    dp[i][w] = newReturn;
                    count[i][w] = count[i][w - price] + 1;
                }
            }
        }
    }
    
    // Backtrack to find allocation
    std::map<std::string, int> allocation;
    int w = W;
    for (int i = n; i > 0 && w > 0; i--) {
        int price = static_cast<int>(prices[i-1]);
        
        while (w >= price && dp[i][w] != dp[i-1][w]) {
            allocation[symbols[i-1]]++;
            w -= price;
        }
    }
    
    return allocation;
}

std::vector<int> DynamicProgrammingAlgorithm::optimalTradeSequence(
    const std::vector<double>& prices,
    const std::vector<int>& quantities,
    int maxTrades) {
    
    int n = prices.size();
    std::vector<int> sequence;
    
    // DP: Find sequence that minimizes total cost
    std::vector<std::vector<double>> dp(n + 1, std::vector<double>(maxTrades + 1, 1e9));
    std::vector<std::vector<int>> parent(n + 1, std::vector<int>(maxTrades + 1, -1));
    
    dp[0][0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int k = 0; k <= maxTrades; k++) {
            // Skip this trade
            if (dp[i-1][k] < dp[i][k]) {
                dp[i][k] = dp[i-1][k];
                parent[i][k] = -1;
            }
            
            // Take this trade
            if (k > 0 && dp[i-1][k-1] + prices[i-1] * quantities[i-1] < dp[i][k]) {
                dp[i][k] = dp[i-1][k-1] + prices[i-1] * quantities[i-1];
                parent[i][k] = i - 1;
            }
        }
    }
    
    // Backtrack
    int k = maxTrades;
    for (int i = n; i > 0; i--) {
        if (parent[i][k] != -1) {
            sequence.push_back(parent[i][k]);
            k--;
        }
    }
    
    std::reverse(sequence.begin(), sequence.end());
    return sequence;
}

std::map<std::string, double> DynamicProgrammingAlgorithm::riskAdjustedAllocation(
    const std::vector<std::string>& symbols,
    const std::vector<double>& expectedReturns,
    const std::vector<double>& risks,
    double riskTolerance) {
    
    std::map<std::string, double> allocation;
    
    // Calculate Sharpe-like ratio for each asset
    std::vector<std::pair<double, int>> ratios;
    for (size_t i = 0; i < symbols.size(); i++) {
        double ratio = expectedReturns[i] / (risks[i] + 1e-6);
        ratios.push_back({ratio, i});
    }
    
    // Sort by ratio (descending)
    std::sort(ratios.begin(), ratios.end(), 
             [](const auto& a, const auto& b) { return a.first > b.first; });
    
    // Allocate based on risk tolerance
    double totalAllocation = 0.0;
    for (const auto& pair : ratios) {
        int idx = pair.second;
        double weight = std::max(0.0, pair.first / (risks[idx] + 1.0));
        allocation[symbols[idx]] = weight;
        totalAllocation += weight;
    }
    
    // Normalize to sum to 1.0
    for (auto& pair : allocation) {
        pair.second /= totalAllocation;
    }
    
    return allocation;
}

// Portfolio implementation
void Portfolio::addPosition(const std::string& symbol, int quantity, double price) {
    if (positions.find(symbol) != positions.end()) {
        // Update existing position
        auto& pos = positions[symbol];
        double totalCost = pos.avgPrice * pos.quantity + price * quantity;
        pos.quantity += quantity;
        pos.avgPrice = totalCost / pos.quantity;
    } else {
        // New position
        Position pos;
        pos.symbol = symbol;
        pos.quantity = quantity;
        pos.avgPrice = price;
        pos.currentPrice = price;
        pos.unrealizedPnL = 0.0;
        positions[symbol] = pos;
    }
    
    cash -= price * quantity;
}

void Portfolio::updatePrice(const std::string& symbol, double newPrice) {
    if (positions.find(symbol) != positions.end()) {
        auto& pos = positions[symbol];
        pos.currentPrice = newPrice;
        pos.unrealizedPnL = (newPrice - pos.avgPrice) * pos.quantity;
    }
}

void Portfolio::displayPortfolio() const {
    std::cout << "\n========== PORTFOLIO ==========" << std::endl;
    std::cout << "Cash: $" << std::fixed << std::setprecision(2) << cash << std::endl;
    std::cout << "Total Value: $" << getTotalValue() << std::endl;
    std::cout << "Total P&L: $" << getTotalPnL() << std::endl;
    std::cout << "\nPositions:" << std::endl;
    std::cout << std::left << std::setw(10) << "Symbol" 
              << std::setw(10) << "Qty" 
              << std::setw(12) << "Avg Price" 
              << std::setw(12) << "Curr Price"
              << std::setw(12) << "P&L" << std::endl;
    std::cout << std::string(56, '-') << std::endl;
    
    for (const auto& pair : positions) {
        const auto& pos = pair.second;
        std::cout << std::left << std::setw(10) << pos.symbol
                  << std::setw(10) << pos.quantity
                  << "$" << std::setw(11) << pos.avgPrice
                  << "$" << std::setw(11) << pos.currentPrice
                  << "$" << std::setw(11) << pos.unrealizedPnL << std::endl;
    }
}

double Portfolio::getTotalValue() const {
    double total = cash;
    for (const auto& pair : positions) {
        total += pair.second.currentPrice * pair.second.quantity;
    }
    return total;
}

double Portfolio::getTotalPnL() const {
    return getTotalValue() - initialCash;
}

// Trading Strategy implementation
std::string TradingStrategy::generateGreedySignal(
    double currentPrice, 
    const std::vector<double>& priceHistory) {
    
    if (priceHistory.size() < 2) return "HOLD";
    
    // Greedy: if price is at local minimum, buy; if at local maximum, sell
    double recentAvg = std::accumulate(priceHistory.end() - 5, priceHistory.end(), 0.0) / 5.0;
    
    if (currentPrice < recentAvg * 0.98) {
        return "BUY";
    } else if (currentPrice > recentAvg * 1.02) {
        return "SELL";
    }
    
    return "HOLD";
}

std::map<std::string, int> TradingStrategy::generateRebalancingOrders(
    const Portfolio& currentPortfolio,
    const std::map<std::string, double>& targetAllocations,
    const std::map<std::string, double>& currentPrices) {
    
    std::map<std::string, int> orders;
    double totalValue = currentPortfolio.getTotalValue();
    
    for (const auto& pair : targetAllocations) {
        const std::string& symbol = pair.first;
        double targetAlloc = pair.second;
        double targetValue = totalValue * targetAlloc;
        
        auto it = currentPrices.find(symbol);
        if (it != currentPrices.end()) {
            double price = it->second;
            int targetQty = static_cast<int>(targetValue / price);
            
            const auto& positions = currentPortfolio.getPositions();
            int currentQty = 0;
            auto posIt = positions.find(symbol);
            if (posIt != positions.end()) {
                currentQty = posIt->second.quantity;
            }
            
            orders[symbol] = targetQty - currentQty;
        }
    }
    
    return orders;
}
