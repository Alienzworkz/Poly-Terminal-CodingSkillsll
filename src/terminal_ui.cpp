#include "../include/terminal_ui.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Terminal UI Implementation
void TerminalUI::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void TerminalUI::printHeader() {
    std::cout << Color::BG_BLUE << Color::WHITE << Color::BOLD;
    std::cout << std::string(80, ' ') << std::endl;
    std::cout << TerminalUtils::centerText("DECENTRALIZED TRADING TERMINAL", 80) << std::endl;
    std::cout << TerminalUtils::centerText("Blockchain-Powered Trading Platform", 80) << std::endl;
    std::cout << std::string(80, ' ') << std::endl;
    std::cout << Color::RESET << std::endl;
}

void TerminalUI::printMarketData() {
    std::cout << Color::CYAN << Color::BOLD << "\n=== MARKET DATA ===" << Color::RESET << std::endl;
    
    std::cout << std::left << std::setw(12) << "Symbol" 
              << std::setw(12) << "Bid" 
              << std::setw(12) << "Ask" 
              << std::setw(12) << "Spread" 
              << std::setw(12) << "Last" << std::endl;
    TerminalUtils::printSeparator(60, '-');
    
    auto symbols = market->getSymbols();
    for (const auto& symbol : symbols) {
        auto ob = market->getOrderBook(symbol);
        if (ob) {
            double bid = ob->getBestBid();
            double ask = ob->getBestAsk();
            double spread = ob->getSpread();
            
            std::cout << std::left << std::setw(12) << symbol
                      << Color::GREEN << formatPrice(bid) << Color::RESET << std::setw(4) << " "
                      << Color::RED << formatPrice(ask) << Color::RESET << std::setw(4) << " "
                      << std::setw(12) << formatPrice(spread, false)
                      << formatPrice((bid + ask) / 2) << std::endl;
        }
    }
}

void TerminalUI::printOrderBook(const std::string& symbol) {
    auto ob = market->getOrderBook(symbol);
    if (!ob) {
        std::cout << Color::RED << "Symbol not found!" << Color::RESET << std::endl;
        return;
    }
    
    std::cout << Color::YELLOW << Color::BOLD 
              << "\n=== ORDER BOOK: " << symbol << " ===" 
              << Color::RESET << std::endl;
    
    ob->display();
}

void TerminalUI::printPortfolio() {
    std::cout << Color::MAGENTA << Color::BOLD 
              << "\n=== PORTFOLIO ===" 
              << Color::RESET << std::endl;
    
    portfolio->displayPortfolio();
}

void TerminalUI::printBlockchain() {
    std::cout << Color::BLUE << Color::BOLD 
              << "\n=== BLOCKCHAIN ===" 
              << Color::RESET << std::endl;
    
    blockchain->displayChain();
}

void TerminalUI::printMenu() {
    std::cout << Color::CYAN << "\n=== MENU ===" << Color::RESET << std::endl;
    std::cout << "1. View Market Data" << std::endl;
    std::cout << "2. View Order Book" << std::endl;
    std::cout << "3. Place Order" << std::endl;
    std::cout << "4. View Portfolio" << std::endl;
    std::cout << "5. View Blockchain" << std::endl;
    std::cout << "6. Mine Pending Trades" << std::endl;
    std::cout << "7. Run Greedy Algorithm Demo" << std::endl;
    std::cout << "8. Run DP Portfolio Optimization" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "\nChoice: ";
}

std::string TerminalUI::formatPrice(double price, bool isPositive) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << "$" << price;
    return ss.str();
}

std::string TerminalUI::formatPercentage(double percentage) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << percentage << "%";
    return ss.str();
}

void TerminalUI::displayMainScreen() {
    clearScreen();
    printHeader();
    printMarketData();
    printMenu();
}

void TerminalUI::displayOrderBookScreen(const std::string& symbol) {
    clearScreen();
    printHeader();
    printOrderBook(symbol);
}

void TerminalUI::displayBlockchainScreen() {
    clearScreen();
    printHeader();
    printBlockchain();
}

void TerminalUI::displayPortfolioScreen() {
    clearScreen();
    printHeader();
    printPortfolio();
}

void TerminalUI::handleUserInput() {
    int choice;
    std::cin >> choice;
    
    switch (choice) {
        case 1: {
            displayMainScreen();
            break;
        }
        case 2: {
            std::string symbol;
            std::cout << "Enter symbol: ";
            std::cin >> symbol;
            displayOrderBookScreen(symbol);
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        case 3: {
            std::string symbol, side, trader;
            double price;
            int quantity;
            
            std::cout << "Enter symbol: ";
            std::cin >> symbol;
            std::cout << "Enter side (BUY/SELL): ";
            std::cin >> side;
            std::cout << "Enter price: ";
            std::cin >> price;
            std::cout << "Enter quantity: ";
            std::cin >> quantity;
            std::cout << "Enter trader name: ";
            std::cin >> trader;
            
            auto ob = market->getOrderBook(symbol);
            if (ob) {
                int orderId = ob->addOrder(price, quantity, side, trader);
                std::cout << Color::GREEN << "Order placed! ID: " << orderId << Color::RESET << std::endl;
                
                // Try to match orders
                auto trades = ob->matchOrders();
                for (const auto& trade : trades) {
                    blockchain->addTrade(trade);
                    std::cout << Color::YELLOW << "Trade executed: " << trade.quantity 
                              << " @ $" << trade.price << Color::RESET << std::endl;
                    
                    // Update portfolio
                    if (trade.buyer == trader) {
                        portfolio->addPosition(symbol, trade.quantity, trade.price);
                    }
                }
            }
            
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        case 4: {
            displayPortfolioScreen();
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        case 5: {
            displayBlockchainScreen();
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        case 6: {
            std::cout << Color::YELLOW << "Mining pending trades..." << Color::RESET << std::endl;
            blockchain->minePendingTrades();
            std::cout << Color::GREEN << "Block mined successfully!" << Color::RESET << std::endl;
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        case 7: {
            // Greedy Algorithm Demo
            std::cout << Color::CYAN << "\n=== GREEDY ALGORITHM DEMO ===" << Color::RESET << std::endl;
            std::vector<double> prices = {100.5, 100.3, 100.7, 100.2, 100.6};
            std::vector<int> quantities = {100, 200, 150, 300, 100};
            
            double avgPrice = GreedyExecutionAlgorithm::findBestExecutionPrice(
                prices, quantities, 500, true);
            
            std::cout << "Best execution price for 500 shares (BUY): $" 
                      << std::fixed << std::setprecision(2) << avgPrice << std::endl;
            
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        case 8: {
            // DP Portfolio Optimization Demo
            std::cout << Color::CYAN << "\n=== DP PORTFOLIO OPTIMIZATION ===" << Color::RESET << std::endl;
            std::vector<std::string> symbols = {"AAPL", "GOOGL", "MSFT", "AMZN"};
            std::vector<double> prices = {150.0, 2800.0, 300.0, 3300.0};
            std::vector<double> returns = {0.15, 0.20, 0.12, 0.18};
            double budget = 10000.0;
            
            auto allocation = DynamicProgrammingAlgorithm::optimizePortfolio(
                symbols, prices, returns, budget);
            
            std::cout << "Optimal allocation with $" << budget << " budget:" << std::endl;
            for (const auto& pair : allocation) {
                std::cout << pair.first << ": " << pair.second << " shares" << std::endl;
            }
            
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        case 9: {
            std::cout << Color::GREEN << "Thank you for using the Decentralized Trading Terminal!" 
                      << Color::RESET << std::endl;
            exit(0);
        }
        default: {
            std::cout << Color::RED << "Invalid choice!" << Color::RESET << std::endl;
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}

void TerminalUI::run() {
    while (true) {
        displayMainScreen();
        handleUserInput();
    }
}

// Utility functions
namespace TerminalUtils {
    void printBox(const std::string& title, const std::vector<std::string>& content, int width) {
        std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;
        std::cout << "| " << centerText(title, width - 4) << " |" << std::endl;
        std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;
        
        for (const auto& line : content) {
            std::cout << "| " << padRight(line, width - 4) << " |" << std::endl;
        }
        
        std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;
    }
    
    void printSeparator(int width, char c) {
        std::cout << std::string(width, c) << std::endl;
    }
    
    std::string centerText(const std::string& text, int width) {
        int padding = (width - text.length()) / 2;
        return std::string(padding, ' ') + text + std::string(width - padding - text.length(), ' ');
    }
    
    std::string padRight(const std::string& text, int width) {
        if (text.length() >= width) return text.substr(0, width);
        return text + std::string(width - text.length(), ' ');
    }
    
    std::string padLeft(const std::string& text, int width) {
        if (text.length() >= width) return text.substr(0, width);
        return std::string(width - text.length(), ' ') + text;
    }
}
