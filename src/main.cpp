#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <algorithm>
#include "../include/blockchain.h"
#include "../include/order_book.h"
#include "../include/trading_algorithms.h"
#include "../include/terminal_ui.h"

void initializeMarket(Market& market) {
    // Add trading symbols
    market.addSymbol("AAPL");
    market.addSymbol("GOOGL");
    market.addSymbol("MSFT");
    market.addSymbol("AMZN");
    market.addSymbol("TSLA");
    
    // Add some initial orders to create market depth
    auto appleBook = market.getOrderBook("AAPL");
    if (appleBook) {
        // Buy orders
        appleBook->addOrder(150.00, 100, "BUY", "MarketMaker1");
        appleBook->addOrder(149.95, 200, "BUY", "MarketMaker1");
        appleBook->addOrder(149.90, 150, "BUY", "MarketMaker2");
        
        // Sell orders
        appleBook->addOrder(150.10, 100, "SELL", "MarketMaker1");
        appleBook->addOrder(150.15, 200, "SELL", "MarketMaker2");
        appleBook->addOrder(150.20, 150, "SELL", "MarketMaker1");
    }
    
    auto googleBook = market.getOrderBook("GOOGL");
    if (googleBook) {
        googleBook->addOrder(2800.00, 50, "BUY", "MarketMaker1");
        googleBook->addOrder(2799.50, 75, "BUY", "MarketMaker2");
        googleBook->addOrder(2801.00, 50, "SELL", "MarketMaker1");
        googleBook->addOrder(2801.50, 75, "SELL", "MarketMaker2");
    }
    
    auto msftBook = market.getOrderBook("MSFT");
    if (msftBook) {
        msftBook->addOrder(300.00, 150, "BUY", "MarketMaker1");
        msftBook->addOrder(299.95, 200, "BUY", "MarketMaker2");
        msftBook->addOrder(300.10, 150, "SELL", "MarketMaker1");
        msftBook->addOrder(300.15, 200, "SELL", "MarketMaker2");
    }
    
    auto amznBook = market.getOrderBook("AMZN");
    if (amznBook) {
        amznBook->addOrder(3300.00, 30, "BUY", "MarketMaker1");
        amznBook->addOrder(3299.50, 50, "BUY", "MarketMaker2");
        amznBook->addOrder(3301.00, 30, "SELL", "MarketMaker1");
        amznBook->addOrder(3301.50, 50, "SELL", "MarketMaker2");
    }
    
    auto teslaBook = market.getOrderBook("TSLA");
    if (teslaBook) {
        teslaBook->addOrder(700.00, 100, "BUY", "MarketMaker1");
        teslaBook->addOrder(699.90, 150, "BUY", "MarketMaker2");
        teslaBook->addOrder(700.20, 100, "SELL", "MarketMaker1");
        teslaBook->addOrder(700.30, 150, "SELL", "MarketMaker2");
    }
}

void demonstrateAlgorithms() {
    std::cout << "\n" << Color::CYAN << Color::BOLD 
              << "========================================" << std::endl;
    std::cout << "  ALGORITHM DEMONSTRATIONS" << std::endl;
    std::cout << "========================================" 
              << Color::RESET << "\n" << std::endl;
    
    // Greedy Algorithm Demo
    std::cout << Color::YELLOW << Color::BOLD << "\n1. GREEDY ALGORITHM - Best Execution Price" 
              << Color::RESET << std::endl;
    std::cout << "   This algorithm finds the optimal average execution price" << std::endl;
    std::cout << "   by greedily selecting from the best price levels.\n" << std::endl;
    
    // Get user input for Greedy Algorithm
    int targetQuantity;
    int numLevels;
    
    std::cout << "   Enter target quantity to buy/sell: ";
    std::cin >> targetQuantity;
    
    std::cout << "   Enter number of price levels available: ";
    std::cin >> numLevels;
    
    std::vector<double> prices;
    std::vector<int> quantities;
    
    std::cout << "\n   Enter price and quantity for each level:" << std::endl;
    for (int i = 0; i < numLevels; i++) {
        double price;
        int qty;
        std::cout << "   Level " << (i+1) << " - Price: $";
        std::cin >> price;
        std::cout << "   Level " << (i+1) << " - Quantity: ";
        std::cin >> qty;
        prices.push_back(price);
        quantities.push_back(qty);
    }
    
    std::cout << "\n   " << Color::CYAN << "Running Greedy Algorithm..." << Color::RESET << std::endl;
    
    double buyPrice = GreedyExecutionAlgorithm::findBestExecutionPrice(
        prices, quantities, targetQuantity, true);
    double sellPrice = GreedyExecutionAlgorithm::findBestExecutionPrice(
        prices, quantities, targetQuantity, false);
    
    std::cout << "\n   " << Color::GREEN << Color::BOLD << "RESULTS:" << Color::RESET << std::endl;
    std::cout << "   Best BUY execution price:  $" 
              << std::fixed << std::setprecision(2) << buyPrice << std::endl;
    std::cout << "   Best SELL execution price: $" 
              << sellPrice << std::endl;
    std::cout << "   Savings: $" << (sellPrice - buyPrice) * targetQuantity << std::endl;
    
    // Dynamic Programming Demo
    std::cout << "\n" << Color::YELLOW << Color::BOLD 
              << "\n2. DYNAMIC PROGRAMMING - Portfolio Optimization" 
              << Color::RESET << std::endl;
    std::cout << "   This algorithm maximizes expected returns given a budget constraint" << std::endl;
    std::cout << "   using dynamic programming (Knapsack variant).\n" << std::endl;
    
    int numStocks;
    double budget;
    
    std::cout << "   Enter your budget: $";
    std::cin >> budget;
    
    std::cout << "   Enter number of stocks to consider: ";
    std::cin >> numStocks;
    
    std::vector<std::string> symbols;
    std::vector<double> stockPrices;
    std::vector<double> expectedReturns;
    
    std::cout << "\n   Enter details for each stock:" << std::endl;
    for (int i = 0; i < numStocks; i++) {
        std::string symbol;
        double price, returnRate;
        
        std::cout << "   Stock " << (i+1) << " - Symbol: ";
        std::cin >> symbol;
        std::cout << "   Stock " << (i+1) << " - Price: $";
        std::cin >> price;
        std::cout << "   Stock " << (i+1) << " - Expected Return (%): ";
        std::cin >> returnRate;
        
        symbols.push_back(symbol);
        stockPrices.push_back(price);
        expectedReturns.push_back(returnRate / 100.0);
    }
    
    std::cout << "\n   " << Color::CYAN << "Running Dynamic Programming Algorithm..." << Color::RESET << std::endl;
    
    auto allocation = DynamicProgrammingAlgorithm::optimizePortfolio(
        symbols, stockPrices, expectedReturns, budget);
    
    std::cout << "\n   " << Color::GREEN << Color::BOLD << "OPTIMAL ALLOCATION:" << Color::RESET << std::endl;
    double totalInvested = 0.0;
    double expectedReturn = 0.0;
    
    for (const auto& pair : allocation) {
        int idx = std::find(symbols.begin(), symbols.end(), pair.first) - symbols.begin();
        double invested = pair.second * stockPrices[idx];
        totalInvested += invested;
        expectedReturn += invested * expectedReturns[idx];
        
        std::cout << "   - " << pair.first << ": " << pair.second 
                  << " shares @ $" << std::fixed << std::setprecision(2) 
                  << stockPrices[idx] << " = $" << invested << std::endl;
    }
    std::cout << "\n   Total invested: $" << totalInvested << std::endl;
    std::cout << "   Cash remaining: $" << (budget - totalInvested) << std::endl;
    std::cout << "   Expected return: $" << expectedReturn << " (" 
              << (expectedReturn/totalInvested*100) << "%)" << std::endl;
    
    // Risk-Adjusted Allocation Demo
    std::cout << "\n" << Color::YELLOW << Color::BOLD 
              << "\n3. DYNAMIC PROGRAMMING - Risk-Adjusted Allocation" 
              << Color::RESET << std::endl;
    std::cout << "   This algorithm allocates portfolio based on risk-return tradeoff.\n" << std::endl;
    
    std::vector<double> risks;
    
    std::cout << "   Enter risk level (volatility %) for each stock:" << std::endl;
    for (int i = 0; i < numStocks; i++) {
        double risk;
        std::cout << "   " << symbols[i] << " - Risk (%): ";
        std::cin >> risk;
        risks.push_back(risk / 100.0);
    }
    
    double riskTolerance;
    std::cout << "\n   Enter your risk tolerance (0.0 - 1.0): ";
    std::cin >> riskTolerance;
    
    std::cout << "\n   " << Color::CYAN << "Running Risk-Adjusted Allocation..." << Color::RESET << std::endl;
    
    auto riskAllocation = DynamicProgrammingAlgorithm::riskAdjustedAllocation(
        symbols, expectedReturns, risks, riskTolerance);
    
    std::cout << "\n   " << Color::GREEN << Color::BOLD << "RISK-ADJUSTED WEIGHTS:" << Color::RESET << std::endl;
    for (const auto& pair : riskAllocation) {
        std::cout << "   - " << pair.first << ": " 
                  << std::fixed << std::setprecision(1) << (pair.second * 100) 
                  << "%" << std::endl;
    }
    
    std::cout << "\n" << Color::CYAN << "Press Enter to continue to trading terminal..." 
              << Color::RESET << std::endl;
    std::cin.ignore();
    std::cin.get();
}

int main() {
    std::cout << Color::BOLD << Color::CYAN;
    std::cout << R"(
    ╔═══════════════════════════════════════════════════════════╗
    ║                                                           ║
    ║     DECENTRALIZED TRADING TERMINAL                        ║
    ║     Blockchain-Powered Algorithmic Trading                ║
    ║                                                           ║
    ║     Algorithms: Greedy, Dynamic Programming               ║
    ║     Features: Order Matching, Portfolio Optimization      ║
    ║                                                           ║
    ╚═══════════════════════════════════════════════════════════╝
    )" << Color::RESET << std::endl;
    
    std::cout << "\nInitializing system..." << std::endl;
    
    // Initialize components
    Blockchain blockchain(2); // Difficulty level 2
    Market market;
    Portfolio portfolio(100000.0); // Starting with $100,000
    
    std::cout << "Setting up market..." << std::endl;
    initializeMarket(market);
    
    std::cout << "System ready!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Demonstrate algorithms
    demonstrateAlgorithms();
    
    // Start terminal UI
    TerminalUI terminal(&market, &blockchain, &portfolio);
    terminal.run();
    
    return 0;
}
