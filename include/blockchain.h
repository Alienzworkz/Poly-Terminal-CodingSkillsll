#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>

// Trade structure
struct Trade {
    std::string symbol;
    double price;
    int quantity;
    std::string buyer;
    std::string seller;
    time_t timestamp;
    std::string type; // "BUY" or "SELL"
};

// Block in the blockchain
class Block {
private:
    int index;
    time_t timestamp;
    std::vector<Trade> trades;
    std::string previousHash;
    std::string hash;
    int nonce;

public:
    std::string calculateHash() const;
    Block(int idx, const std::vector<Trade>& trades, const std::string& prevHash);
    
    void mineBlock(int difficulty);
    std::string getHash() const { return hash; }
    std::string getPreviousHash() const { return previousHash; }
    int getIndex() const { return index; }
    const std::vector<Trade>& getTrades() const { return trades; }
    time_t getTimestamp() const { return timestamp; }
    
    void display() const;
};

// Blockchain
class Blockchain {
private:
    std::vector<Block> chain;
    int difficulty;
    std::vector<Trade> pendingTrades;

    Block createGenesisBlock();

public:
    Blockchain(int diff = 2);
    
    void addTrade(const Trade& trade);
    void minePendingTrades();
    bool isChainValid() const;
    void displayChain() const;
    void displayPendingTrades() const;
    const std::vector<Block>& getChain() const { return chain; }
};

#endif
