#ifndef TERMINAL_UI_H
#define TERMINAL_UI_H

#include <string>
#include <vector>
#include <map>
#include "blockchain.h"
#include "order_book.h"
#include "trading_algorithms.h"

// ANSI color codes
namespace Color {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string BOLD = "\033[1m";
    const std::string BG_BLACK = "\033[40m";
    const std::string BG_BLUE = "\033[44m";
}

class TerminalUI {
private:
    Market* market;
    Blockchain* blockchain;
    Portfolio* portfolio;
    
    void clearScreen();
    void printHeader();
    void printMarketData();
    void printOrderBook(const std::string& symbol);
    void printPortfolio();
    void printMenu();
    void printBlockchain();
    
    std::string formatPrice(double price, bool isPositive = true);
    std::string formatPercentage(double percentage);
    
public:
    TerminalUI(Market* m, Blockchain* bc, Portfolio* p) 
        : market(m), blockchain(bc), portfolio(p) {}
    
    void displayMainScreen();
    void displayOrderBookScreen(const std::string& symbol);
    void displayBlockchainScreen();
    void displayPortfolioScreen();
    
    void handleUserInput();
    void run();
};

// Utility functions
namespace TerminalUtils {
    void printBox(const std::string& title, const std::vector<std::string>& content, int width = 80);
    void printSeparator(int width = 80, char c = '=');
    std::string centerText(const std::string& text, int width);
    std::string padRight(const std::string& text, int width);
    std::string padLeft(const std::string& text, int width);
}

#endif
