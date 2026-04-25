#ifndef SALE_H
#define SALE_H

#include <string>

class Sale {
private:
    int productId;
    std::string productName;
    int quantity;
    double totalAmount;

public:
    Sale();
    Sale(int productId, const std::string& productName, int quantity, double totalAmount);

    int getProductId() const;
    std::string getProductName() const;
    int getQuantity() const;
    double getTotalAmount() const;

    std::string serialize() const;
    static Sale deserialize(const std::string& line);
};

#endif
