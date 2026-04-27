#include "../include/blockchain.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

// Helper function to calculate SHA256 hash
std::string sha256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Block implementation
Block::Block(int idx, const std::vector<Trade>& t, const std::string& prevHash)
    : index(idx), trades(t), previousHash(prevHash), nonce(0) {
    timestamp = time(nullptr);
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << previousHash << nonce;
    
    for (const auto& trade : trades) {
        ss << trade.symbol << trade.price << trade.quantity 
           << trade.buyer << trade.seller << trade.timestamp;
    }
    
    return sha256(ss.str());
}

void Block::mineBlock(int difficulty) {
    std::string target(difficulty, '0');
    
    while (hash.substr(0, difficulty) != target) {
        nonce++;
        hash = calculateHash();
    }
    
    std::cout << "Block mined: " << hash << std::endl;
}

void Block::display() const {
    std::cout << "\n=== Block #" << index << " ===" << std::endl;
    std::cout << "Timestamp: " << ctime(&timestamp);
    std::cout << "Hash: " << hash << std::endl;
    std::cout << "Previous Hash: " << previousHash << std::endl;
    std::cout << "Nonce: " << nonce << std::endl;
    std::cout << "Trades in block: " << trades.size() << std::endl;
    
    for (size_t i = 0; i < trades.size(); i++) {
        const auto& trade = trades[i];
        std::cout << "  Trade " << (i+1) << ": " 
                  << trade.symbol << " | "
                  << trade.quantity << " @ $" << trade.price << " | "
                  << trade.buyer << " <- " << trade.seller << std::endl;
    }
}

// Blockchain implementation
Blockchain::Blockchain(int diff) : difficulty(diff) {
    chain.push_back(createGenesisBlock());
}

Block Blockchain::createGenesisBlock() {
    std::vector<Trade> genesisData;
    return Block(0, genesisData, "0");
}

void Blockchain::addTrade(const Trade& trade) {
    pendingTrades.push_back(trade);
}

void Blockchain::minePendingTrades() {
    if (pendingTrades.empty()) {
        std::cout << "No pending trades to mine." << std::endl;
        return;
    }
    
    Block newBlock(chain.size(), pendingTrades, chain.back().getHash());
    newBlock.mineBlock(difficulty);
    chain.push_back(newBlock);
    
    pendingTrades.clear();
}

bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < chain.size(); i++) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];
        
        if (currentBlock.getHash() != currentBlock.calculateHash()) {
            return false;
        }
        
        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            return false;
        }
    }
    return true;
}

void Blockchain::displayChain() const {
    std::cout << "\n========== BLOCKCHAIN ==========" << std::endl;
    std::cout << "Total Blocks: " << chain.size() << std::endl;
    std::cout << "Chain Valid: " << (isChainValid() ? "YES" : "NO") << std::endl;
    
    for (const auto& block : chain) {
        block.display();
    }
}

void Blockchain::displayPendingTrades() const {
    std::cout << "\n=== Pending Trades ===" << std::endl;
    std::cout << "Count: " << pendingTrades.size() << std::endl;
    
    for (size_t i = 0; i < pendingTrades.size(); i++) {
        const auto& trade = pendingTrades[i];
        std::cout << (i+1) << ". " << trade.symbol << " | "
                  << trade.quantity << " @ $" << trade.price << " | "
                  << trade.buyer << " <- " << trade.seller << std::endl;
    }
}
