#include "../include/order_book.h"
#include "../include/blockchain.h"
#include <iostream>
#include <iomanip>

// OrderBook implementation
int OrderBook::addOrder(double price, int quantity, const std::string& side, const std::string& trader) {
    auto order = std::make_shared<Order>(nextOrderId++, symbol, price, quantity, side, trader);
    allOrders[order->orderId] = order;
    
    if (side == "BUY") {
        buyOrders.push(order);
    } else {
        sellOrders.push(order);
    }
    
    return order->orderId;
}

bool OrderBook::cancelOrder(int orderId) {
    auto it = allOrders.find(orderId);
    if (it != allOrders.end()) {
        allOrders.erase(it);
        return true;
    }
    return false;
}

std::vector<Trade> OrderBook::matchOrders() {
    std::vector<Trade> executedTrades;
    
    while (!buyOrders.empty() && !sellOrders.empty()) {
        auto topBuy = buyOrders.top();
        auto topSell = sellOrders.top();
        
        // Check if orders can be matched
        if (topBuy->price >= topSell->price) {
            // Match found!
            int matchedQuantity = std::min(topBuy->quantity, topSell->quantity);
            double executionPrice = topSell->price; // Price-time priority
            
            Trade trade;
            trade.symbol = symbol;
            trade.price = executionPrice;
            trade.quantity = matchedQuantity;
            trade.buyer = topBuy->trader;
            trade.seller = topSell->trader;
            trade.timestamp = time(nullptr);
            trade.type = "MATCHED";
            
            executedTrades.push_back(trade);
            
            // Update quantities
            topBuy->quantity -= matchedQuantity;
            topSell->quantity -= matchedQuantity;
            
            // Remove filled orders
            if (topBuy->quantity == 0) {
                buyOrders.pop();
                allOrders.erase(topBuy->orderId);
            }
            if (topSell->quantity == 0) {
                sellOrders.pop();
                allOrders.erase(topSell->orderId);
            }
        } else {
            break; // No more matches possible
        }
    }
    
    return executedTrades;
}

void OrderBook::display() const {
    std::cout << "\n=== Order Book: " << symbol << " ===" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    
    // Display sell orders (asks)
    std::cout << "\n--- ASKS (Sell Orders) ---" << std::endl;
    auto tempSell = sellOrders;
    int count = 0;
    while (!tempSell.empty() && count < 5) {
        auto order = tempSell.top();
        std::cout << "$" << std::setw(8) << order->price 
                  << " | " << std::setw(6) << order->quantity 
                  << " | " << order->trader << std::endl;
        tempSell.pop();
        count++;
    }
    
    std::cout << "\n--- Spread: $" << getSpread() << " ---" << std::endl;
    
    // Display buy orders (bids)
    std::cout << "\n--- BIDS (Buy Orders) ---" << std::endl;
    auto tempBuy = buyOrders;
    count = 0;
    while (!tempBuy.empty() && count < 5) {
        auto order = tempBuy.top();
        std::cout << "$" << std::setw(8) << order->price 
                  << " | " << std::setw(6) << order->quantity 
                  << " | " << order->trader << std::endl;
        tempBuy.pop();
        count++;
    }
}

double OrderBook::getBestBid() const {
    if (buyOrders.empty()) return 0.0;
    return buyOrders.top()->price;
}

double OrderBook::getBestAsk() const {
    if (sellOrders.empty()) return 0.0;
    return sellOrders.top()->price;
}

double OrderBook::getSpread() const {
    if (buyOrders.empty() || sellOrders.empty()) return 0.0;
    return getBestAsk() - getBestBid();
}

// Market implementation
void Market::addSymbol(const std::string& symbol) {
    orderBooks[symbol] = std::make_shared<OrderBook>(symbol);
}

OrderBook* Market::getOrderBook(const std::string& symbol) {
    auto it = orderBooks.find(symbol);
    if (it != orderBooks.end()) {
        return it->second.get();
    }
    return nullptr;
}

std::vector<std::string> Market::getSymbols() const {
    std::vector<std::string> symbols;
    for (const auto& pair : orderBooks) {
        symbols.push_back(pair.first);
    }
    return symbols;
}

void Market::displayMarket() const {
    std::cout << "\n========== MARKET DATA ==========" << std::endl;
    std::cout << std::left << std::setw(10) << "Symbol" 
              << std::setw(12) << "Bid" 
              << std::setw(12) << "Ask" 
              << std::setw(12) << "Spread" << std::endl;
    std::cout << std::string(46, '-') << std::endl;
    
    for (const auto& pair : orderBooks) {
        const auto& ob = pair.second;
        std::cout << std::left << std::setw(10) << pair.first
                  << std::fixed << std::setprecision(2)
                  << "$" << std::setw(11) << ob->getBestBid()
                  << "$" << std::setw(11) << ob->getBestAsk()
                  << "$" << std::setw(11) << ob->getSpread() << std::endl;
    }
}
