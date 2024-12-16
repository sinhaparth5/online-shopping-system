#pragma once
#include <string>

class Product {
    private:
    int id;
    std::string name;
    std::string decription;
    double price;
    int stockQuantity;

    public:
    Product(int id, std::string name, std::string decription, double price, int stockQuantity);

    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getDecription() const { return decription; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stockQuantity; }

    //Setters
    void setPrice(double newPrice);
    void setStockQuantity(int newStockQuantity);
    bool isAvailable() const;
};
