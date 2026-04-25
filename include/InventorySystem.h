#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <string>
#include <vector>
#include "Product.h"
#include "Sale.h"

class InventorySystem {
private:
    std::vector<Product> products;
    std::vector<Sale> sales;
    std::string productFile;
    std::string salesFile;

    void loadProducts();
    void saveProducts() const;
    void loadSales();
    void saveSales() const;

    int generateProductId() const;
    Product* findProductById(int id);

    void showMenu() const;
    void addProduct();
    void listProducts() const;
    void updateStock();
    void recordSale();
    void showSalesReport() const;
    void showLowStockProducts() const;

public:
    InventorySystem(const std::string& productFile, const std::string& salesFile);
    void run();
};

#endif
