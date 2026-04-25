#include "Sale.h"
#include <sstream>
#include <stdexcept>
#include <vector>

Sale::Sale() : productId(0), quantity(0), totalAmount(0.0) {}

Sale::Sale(int productId, const std::string& productName, int quantity, double totalAmount)
    : productId(productId), productName(productName), quantity(quantity), totalAmount(totalAmount) {}

int Sale::getProductId() const { return productId; }
std::string Sale::getProductName() const { return productName; }
int Sale::getQuantity() const { return quantity; }
double Sale::getTotalAmount() const { return totalAmount; }

std::string Sale::serialize() const {
    std::ostringstream out;
    out << productId << "|" << productName << "|" << quantity << "|" << totalAmount;
    return out.str();
}

Sale Sale::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string part;
    std::vector<std::string> parts;

    while (std::getline(ss, part, '|')) {
        parts.push_back(part);
    }

    if (parts.size() != 4) {
        throw std::runtime_error("Invalid sale data format.");
    }

    return Sale(
        std::stoi(parts[0]),
        parts[1],
        std::stoi(parts[2]),
        std::stod(parts[3])
    );
}
