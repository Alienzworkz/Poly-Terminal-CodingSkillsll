#!/bin/bash
# Build script for Linux/Mac

echo "Building Decentralized Trading Terminal..."

# Create obj directory if it doesn't exist
mkdir -p obj

# Compile source files
echo "Compiling blockchain.cpp..."
g++ -std=c++17 -Wall -Iinclude -c src/blockchain.cpp -o obj/blockchain.o

echo "Compiling order_book.cpp..."
g++ -std=c++17 -Wall -Iinclude -c src/order_book.cpp -o obj/order_book.o

echo "Compiling trading_algorithms.cpp..."
g++ -std=c++17 -Wall -Iinclude -c src/trading_algorithms.cpp -o obj/trading_algorithms.o

echo "Compiling terminal_ui.cpp..."
g++ -std=c++17 -Wall -Iinclude -c src/terminal_ui.cpp -o obj/terminal_ui.o

echo "Compiling main.cpp..."
g++ -std=c++17 -Wall -Iinclude -c src/main.cpp -o obj/main.o

# Link all object files
echo "Linking..."
g++ obj/blockchain.o obj/order_book.o obj/trading_algorithms.o obj/terminal_ui.o obj/main.o -o trading_terminal -lcrypto -lssl

if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful!"
    echo "Run with: ./trading_terminal"
    chmod +x trading_terminal
else
    echo ""
    echo "Build failed! Make sure you have:"
    echo "1. g++ compiler installed"
    echo "2. OpenSSL library installed"
    echo ""
    echo "To install dependencies:"
    echo "Ubuntu/Debian: sudo apt-get install build-essential libssl-dev"
    echo "Mac: brew install openssl"
fi
