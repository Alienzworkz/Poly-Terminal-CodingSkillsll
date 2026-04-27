#ifndef TRADING_ALGORITHMS_H
#define TRADING_ALGORITHMS_H

#include <vector>
#include <string>
#include <map>
#include "order_book.h"

// Portfolio position
struct Position {
    std::string symbol;
    int quantity;
    double avgPrice;
    double currentPrice;
    double unrealizedPnL;
};

// Greedy Algorithm: Best Execution Price Selection
class GreedyExecutionAlgorithm {
public:
    // Find best execution price across multiple venues/order books
    static double findBestExecutionPrice(const std::vector<double>& prices, 
                                         const std::vector<int>& quantities,
                                         int targetQuantity,
                                         bool isBuy);
    
    // Greedy order splitting for minimal market impact
    static std::vector<std::pair<double, int>> splitOrder(
        const std::vector<std::pair<double, int>>& orderBookLevels,
        int totalQuantity,
        bool isBuy);
};

// Dynamic Programming: Portfolio Optimization
class DynamicProgrammingAlgorithm {
public:
    // Knapsack-based portfolio optimization
    // Given budget and expected returns, find optimal allocation
    static std::map<std::string, int> optimizePortfolio(
        const std::vector<std::string>& symbols,
        const std::vector<double>& prices,
        const std::vector<double>& expectedReturns,
        double budget);
    
    // Optimal trade sequencing to minimize cost
    static std::vector<int> optimalTradeSequence(
        const std::vector<double>& prices,
        const std::vector<int>& quantities,
        int maxTrades);
    
    // Risk-adjusted portfolio allocation
    static std::map<std::string, double> riskAdjustedAllocation(
        const std::vector<std::string>& symbols,
        const std::vector<double>& expectedReturns,
        const std::vector<double>& risks,
        double riskTolerance);
};

// Portfolio Manager
class Portfolio {
private:
    std::map<std::string, Position> positions;
    double cash;
    double initialCash;
    
public:
    Portfolio(double initialCash) : cash(initialCash), initialCash(initialCash) {}
    
    void addPosition(const std::string& symbol, int quantity, double price);
    void updatePrice(const std::string& symbol, double newPrice);
    void displayPortfolio() const;
    
    double getTotalValue() const;
    double getTotalPnL() const;
    double getCash() const { return cash; }
    
    const std::map<std::string, Position>& getPositions() const { return positions; }
};

// Trading Strategy using algorithms
class TradingStrategy {
public:
    // Generate trading signals using greedy approach
    static std::string generateGreedySignal(double currentPrice, 
                                           const std::vector<double>& priceHistory);
    
    // Generate optimal portfolio rebalancing using DP
    static std::map<std::string, int> generateRebalancingOrders(
        const Portfolio& currentPortfolio,
        const std::map<std::string, double>& targetAllocations,
        const std::map<std::string, double>& currentPrices);
};

#endif
