#include <iostream>
#include "InventorySystem.h"

int main() {
    try {
        InventorySystem system("data/products.txt", "data/sales.txt");
        system.run();
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
