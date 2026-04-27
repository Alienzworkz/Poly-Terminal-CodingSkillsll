# Setup Guide

## Prerequisites

### Windows
1. **C++ Compiler**: Install MinGW-w64 or Visual Studio with C++ support
   - Download MinGW-w64: https://www.mingw-w64.org/
   - Or Visual Studio: https://visualstudio.microsoft.com/

2. **OpenSSL Library**: Required for blockchain hashing
   - Download from: https://slproweb.com/products/Win32OpenSSL.html
   - Or use vcpkg: `vcpkg install openssl`

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential libssl-dev
```

### macOS
```bash
# Install Xcode Command Line Tools
xcode-select --install

# Install OpenSSL
brew install openssl
```

## Building the Project

### Option 1: Using Build Scripts

**Windows:**
```bash
build.bat
```

**Linux/Mac:**
```bash
chmod +x build.sh
./build.sh
```

### Option 2: Using Makefile (Linux/Mac)
```bash
make
```

### Option 3: Manual Compilation
```bash
# Create object directory
mkdir obj

# Compile all source files
g++ -std=c++17 -Iinclude -c src/blockchain.cpp -o obj/blockchain.o
g++ -std=c++17 -Iinclude -c src/order_book.cpp -o obj/order_book.o
g++ -std=c++17 -Iinclude -c src/trading_algorithms.cpp -o obj/trading_algorithms.o
g++ -std=c++17 -Iinclude -c src/terminal_ui.cpp -o obj/terminal_ui.o
g++ -std=c++17 -Iinclude -c src/main.cpp -o obj/main.o

# Link
g++ obj/*.o -o trading_terminal -lcrypto -lssl
```

## Running the Terminal

**Windows:**
```bash
trading_terminal.exe
```

**Linux/Mac:**
```bash
./trading_terminal
```

## Troubleshooting

### OpenSSL Not Found
If you get "cannot find -lcrypto" or similar errors:

**Windows:**
- Make sure OpenSSL is installed
- Add OpenSSL to your PATH
- Or specify the library path: `-L"C:\Program Files\OpenSSL-Win64\lib"`

**Linux:**
```bash
sudo apt-get install libssl-dev
```

**Mac:**
```bash
brew install openssl
# If still not found, add to compiler flags:
# -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include
```

### Compiler Not Found
Make sure g++ is in your PATH:
```bash
g++ --version
```

If not found, install the appropriate compiler for your system.

## Project Structure
```
.
├── include/              # Header files
│   ├── blockchain.h
│   ├── order_book.h
│   ├── trading_algorithms.h
│   └── terminal_ui.h
├── src/                  # Source files
│   ├── blockchain.cpp
│   ├── order_book.cpp
│   ├── trading_algorithms.cpp
│   ├── terminal_ui.cpp
│   └── main.cpp
├── obj/                  # Compiled object files (created during build)
├── README.md             # Project overview
├── ALGORITHMS.md         # Algorithm documentation
├── SETUP.md             # This file
├── Makefile             # Build configuration (Linux/Mac)
├── build.sh             # Build script (Linux/Mac)
└── build.bat            # Build script (Windows)
```

## Features to Test

1. **View Market Data**: See real-time bid/ask prices
2. **Order Book**: View depth of market for each symbol
3. **Place Orders**: Submit buy/sell orders
4. **Order Matching**: Automatic matching using price-time priority
5. **Blockchain**: View immutable trade records
6. **Greedy Algorithm**: Optimal execution price calculation
7. **Dynamic Programming**: Portfolio optimization
8. **Portfolio Tracking**: Monitor positions and P&L

## Next Steps

After successful build:
1. Run the terminal
2. Explore the algorithm demonstrations
3. Place some test orders
4. View the blockchain to see recorded trades
5. Try the portfolio optimization features

## Support

For issues or questions:
- Check the README.md for feature documentation
- Review ALGORITHMS.md for algorithm details
- Ensure all dependencies are properly installed
