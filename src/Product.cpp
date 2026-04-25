#include "Product.h"
#include <sstream>
#include <stdexcept>
#include <vector>

Product::Product() : id(0), price(0.0), stock(0) {}

Product::Product(int id, const std::string& name, const std::string& category, double price, int stock)
    : id(id), name(name), category(category), price(price), stock(stock) {}

int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }

void Product::setName(const std::string& value) { name = value; }
void Product::setCategory(const std::string& value) { category = value; }
void Product::setPrice(double value) { price = value; }
void Product::setStock(int value) { stock = value; }

std::string Product::serialize() const {
    std::ostringstream out;
    out << id << "|" << name << "|" << category << "|" << price << "|" << stock;
    return out.str();
}

Product Product::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string part;
    std::vector<std::string> parts;

    while (std::getline(ss, part, '|')) {
        parts.push_back(part);
    }

    if (parts.size() != 5) {
        throw std::runtime_error("Invalid product data format.");
    }

    return Product(
        std::stoi(parts[0]),
        parts[1],
        parts[2],
        std::stod(parts[3]),
        std::stoi(parts[4])
    );
}
