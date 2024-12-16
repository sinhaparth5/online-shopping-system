#pragma once
#include <string>

class Product {
private:
    int id;
    std::string name;
    std::string description;
    double price;
    int stockQuantity;

public:
    Product(int id, std::string name, std::string description, double price, int stockQuantity);
    
    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stockQuantity; }
    
    // Setters
    void setPrice(double newPrice);
    void updateStock(int quantity);
    bool isAvailable() const;
};