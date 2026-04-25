#include "InventorySystem.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

InventorySystem::InventorySystem(const std::string& productFile, const std::string& salesFile)
    : productFile(productFile), salesFile(salesFile) {
    loadProducts();
    loadSales();
}

void InventorySystem::loadProducts() {
    products.clear();
    std::ifstream file(productFile);
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            products.push_back(Product::deserialize(line));
        }
    }
}

void InventorySystem::saveProducts() const {
    std::ofstream file(productFile, std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Could not save products.");
    }

    for (const auto& product : products) {
        file << product.serialize() << "\n";
    }
}

void InventorySystem::loadSales() {
    sales.clear();
    std::ifstream file(salesFile);
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            sales.push_back(Sale::deserialize(line));
        }
    }
}

void InventorySystem::saveSales() const {
    std::ofstream file(salesFile, std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Could not save sales.");
    }

    for (const auto& sale : sales) {
        file << sale.serialize() << "\n";
    }
}

int InventorySystem::generateProductId() const {
    int maxId = 0;
    for (const auto& product : products) {
        if (product.getId() > maxId) {
            maxId = product.getId();
        }
    }
    return maxId + 1;
}

Product* InventorySystem::findProductById(int id) {
    for (auto& product : products) {
        if (product.getId() == id) {
            return &product;
        }
    }
    return nullptr;
}

void InventorySystem::showMenu() const {
    std::cout << "\n=== Retail Inventory & Sales System ===\n";
    std::cout << "1. Add product\n";
    std::cout << "2. List products\n";
    std::cout << "3. Update stock\n";
    std::cout << "4. Record sale\n";
    std::cout << "5. Show sales report\n";
    std::cout << "6. Show low stock products\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

void InventorySystem::addProduct() {
    std::string name, category;
    double price;
    int stock;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Product name: ";
    std::getline(std::cin, name);

    std::cout << "Category: ";
    std::getline(std::cin, category);

    std::cout << "Price: ";
    std::cin >> price;

    std::cout << "Stock quantity: ";
    std::cin >> stock;

    products.emplace_back(generateProductId(), name, category, price, stock);
    saveProducts();

    std::cout << "Product added successfully.\n";
}

void InventorySystem::listProducts() const {
    if (products.empty()) {
        std::cout << "No products found.\n";
        return;
    }

    std::cout << "\n"
              << std::left
              << std::setw(6) << "ID"
              << std::setw(25) << "Name"
              << std::setw(20) << "Category"
              << std::setw(12) << "Price"
              << std::setw(10) << "Stock" << "\n";

    std::cout << std::string(73, '-') << "\n";

    for (const auto& product : products) {
        std::cout << std::left
                  << std::setw(6) << product.getId()
                  << std::setw(25) << product.getName()
                  << std::setw(20) << product.getCategory()
                  << std::setw(12) << std::fixed << std::setprecision(2) << product.getPrice()
                  << std::setw(10) << product.getStock() << "\n";
    }
}

void InventorySystem::updateStock() {
    int id, newStock;
    std::cout << "Enter product ID: ";
    std::cin >> id;

    Product* product = findProductById(id);
    if (!product) {
        std::cout << "Product not found.\n";
        return;
    }

    std::cout << "New stock quantity: ";
    std::cin >> newStock;

    product->setStock(newStock);
    saveProducts();

    std::cout << "Stock updated successfully.\n";
}

void InventorySystem::recordSale() {
    int id, quantity;
    std::cout << "Enter product ID: ";
    std::cin >> id;

    Product* product = findProductById(id);
    if (!product) {
        std::cout << "Product not found.\n";
        return;
    }

    std::cout << "Quantity sold: ";
    std::cin >> quantity;

    if (quantity <= 0) {
        std::cout << "Invalid quantity.\n";
        return;
    }

    if (product->getStock() < quantity) {
        std::cout << "Not enough stock.\n";
        return;
    }

    product->setStock(product->getStock() - quantity);
    double totalAmount = quantity * product->getPrice();

    sales.emplace_back(product->getId(), product->getName(), quantity, totalAmount);

    saveProducts();
    saveSales();

    std::cout << "Sale recorded successfully. Total: " << std::fixed << std::setprecision(2)
              << totalAmount << "\n";
}

void InventorySystem::showSalesReport() const {
    if (sales.empty()) {
        std::cout << "No sales recorded yet.\n";
        return;
    }

    int totalUnits = 0;
    double totalRevenue = 0.0;

    std::cout << "\nSales History:\n";
    std::cout << std::left
              << std::setw(10) << "Prod ID"
              << std::setw(25) << "Product"
              << std::setw(10) << "Qty"
              << std::setw(12) << "Revenue" << "\n";

    std::cout << std::string(57, '-') << "\n";

    for (const auto& sale : sales) {
        totalUnits += sale.getQuantity();
        totalRevenue += sale.getTotalAmount();

        std::cout << std::left
                  << std::setw(10) << sale.getProductId()
                  << std::setw(25) << sale.getProductName()
                  << std::setw(10) << sale.getQuantity()
                  << std::setw(12) << std::fixed << std::setprecision(2) << sale.getTotalAmount()
                  << "\n";
    }

    std::cout << "\nTotal units sold: " << totalUnits << "\n";
    std::cout << "Total revenue: " << std::fixed << std::setprecision(2) << totalRevenue << "\n";
}

void InventorySystem::showLowStockProducts() const {
    bool found = false;
    std::cout << "\nLow Stock Products (stock <= 5):\n";

    for (const auto& product : products) {
        if (product.getStock() <= 5) {
            found = true;
            std::cout << "- " << product.getName() << " (" << product.getStock() << " left)\n";
        }
    }

    if (!found) {
        std::cout << "No low-stock products.\n";
    }
}

void InventorySystem::run() {
    int choice;
    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: listProducts(); break;
            case 3: updateStock(); break;
            case 4: recordSale(); break;
            case 5: showSalesReport(); break;
            case 6: showLowStockProducts(); break;
            case 0: std::cout << "Exiting application.\n"; break;
            default: std::cout << "Invalid option. Try again.\n"; break;
        }
    } while (choice != 0);
}
