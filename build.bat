@echo off
REM Build script for Windows

echo Building Decentralized Trading Terminal...

REM Create obj directory if it doesn't exist
if not exist obj mkdir obj

REM Compile source files
echo Compiling blockchain.cpp...
g++ -std=c++17 -Wall -Iinclude -c src/blockchain.cpp -o obj/blockchain.o

echo Compiling order_book.cpp...
g++ -std=c++17 -Wall -Iinclude -c src/order_book.cpp -o obj/order_book.o

echo Compiling trading_algorithms.cpp...
g++ -std=c++17 -Wall -Iinclude -c src/trading_algorithms.cpp -o obj/trading_algorithms.o

echo Compiling terminal_ui.cpp...
g++ -std=c++17 -Wall -Iinclude -c src/terminal_ui.cpp -o obj/terminal_ui.o

echo Compiling main.cpp...
g++ -std=c++17 -Wall -Iinclude -c src/main.cpp -o obj/main.o

REM Link all object files
echo Linking...
g++ obj/blockchain.o obj/order_book.o obj/trading_algorithms.o obj/terminal_ui.o obj/main.o -o trading_terminal.exe -lcrypto -lssl

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful!
    echo Run with: trading_terminal.exe
) else (
    echo.
    echo Build failed! Make sure you have:
    echo 1. MinGW-w64 or similar C++ compiler installed
    echo 2. OpenSSL library installed
    echo.
    echo To install OpenSSL on Windows:
    echo - Download from: https://slproweb.com/products/Win32OpenSSL.html
    echo - Or use vcpkg: vcpkg install openssl
)

pause
