#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    std::string category;
    double price;
    int stock;

public:
    Product();
    Product(int id, const std::string& name, const std::string& category, double price, int stock);

    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    int getStock() const;

    void setName(const std::string& value);
    void setCategory(const std::string& value);
    void setPrice(double value);
    void setStock(int value);

    std::string serialize() const;
    static Product deserialize(const std::string& line);
};

#endif
