# C++ Retail Inventory & Sales System

Console-based C++ project for managing products, stock, and sales.

## Features
- Add products
- List products
- Update stock
- Record sales
- View total revenue and units sold
- See low-stock alerts
- File-based persistence with `.txt` files

## Tech
- C++
- OOP
- File handling
- STL

## Build
### g++
```bash
g++ src/*.cpp -Iinclude -o inventory_app
./inventory_app
```

### Windows (MinGW)
```bash
g++ src/*.cpp -Iinclude -o inventory_app.exe
inventory_app.exe
```

## Project Structure
- `src/` → source files
- `include/` → header files
- `data/` → product and sales records

## Why this project is useful
This project is good for GitHub because it shows:
- object-oriented programming
- real business logic
- inventory and sales workflow
- file persistence
