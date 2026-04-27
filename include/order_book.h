#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <ctime>

// Forward declaration - Trade is defined in blockchain.h
struct Trade;

// Order structure
struct Order {
    int orderId;
    std::string symbol;
    double price;
    int quantity;
    std::string side; // "BUY" or "SELL"
    time_t timestamp;
    std::string trader;
    
    Order(int id, const std::string& sym, double p, int qty, 
          const std::string& s, const std::string& t)
        : orderId(id), symbol(sym), price(p), quantity(qty), 
          side(s), timestamp(time(nullptr)), trader(t) {}
};

// Comparator for buy orders (max heap - highest price first)
struct BuyOrderComparator {
    bool operator()(const std::shared_ptr<Order>& a, const std::shared_ptr<Order>& b) const {
        if (a->price != b->price) return a->price < b->price; // Higher price first
        return a->timestamp > b->timestamp; // Earlier timestamp first
    }
};

// Comparator for sell orders (min heap - lowest price first)
struct SellOrderComparator {
    bool operator()(const std::shared_ptr<Order>& a, const std::shared_ptr<Order>& b) const {
        if (a->price != b->price) return a->price > b->price; // Lower price first
        return a->timestamp > b->timestamp; // Earlier timestamp first
    }
};

// Order Book for a single symbol
class OrderBook {
private:
    std::string symbol;
    std::priority_queue<std::shared_ptr<Order>, 
                       std::vector<std::shared_ptr<Order>>, 
                       BuyOrderComparator> buyOrders;
    std::priority_queue<std::shared_ptr<Order>, 
                       std::vector<std::shared_ptr<Order>>, 
                       SellOrderComparator> sellOrders;
    
    std::map<int, std::shared_ptr<Order>> allOrders;
    int nextOrderId;

public:
    OrderBook(const std::string& sym) : symbol(sym), nextOrderId(1) {}
    
    int addOrder(double price, int quantity, const std::string& side, const std::string& trader);
    bool cancelOrder(int orderId);
    std::vector<Trade> matchOrders(); // Returns executed trades
    
    void display() const;
    double getBestBid() const;
    double getBestAsk() const;
    double getSpread() const;
    
    std::string getSymbol() const { return symbol; }
};

// Market - manages multiple order books
class Market {
private:
    std::map<std::string, std::shared_ptr<OrderBook>> orderBooks;
    
public:
    Market() {}
    
    void addSymbol(const std::string& symbol);
    OrderBook* getOrderBook(const std::string& symbol);
    std::vector<std::string> getSymbols() const;
    void displayMarket() const;
};

#endif
