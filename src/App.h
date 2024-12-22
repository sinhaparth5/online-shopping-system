#pragma once
#include "controllers/ProductController.h"
#include <vector>
#include <string>

class App {
public:
    static void run();

private:
    static void clearInputStream();
    static void displayMenu();
    static void displayProducts(const std::vector<Product>& products);
    static void addNewProduct(ProductController& controller);
    static void updateProduct(ProductController& controller);
    static void deleteProduct(ProductController& controller);
    static void searchProducts(ProductController& controller);
    static void updateStock(ProductController& controller);
};