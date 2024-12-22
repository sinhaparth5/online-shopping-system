// src/models/Product.cpp
#include "Product.h"

Product::Product(int id, std::string name, std::string description, double price, int stockQuantity)
    : id(id), 
      name(std::move(name)), 
      description(std::move(description)), 
      price(price), 
      stockQuantity(stockQuantity) {
    // Constructor implementation for the linker
}

void Product::setPrice(double newPrice) {
    if (newPrice >= 0) {
        price = newPrice;
    }
}

void Product::updateStock(int quantity) {
    stockQuantity += quantity;
    if (stockQuantity < 0) {
        stockQuantity = 0;
    }
}

bool Product::isAvailable() const {
    return stockQuantity > 0;
}