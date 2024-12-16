#pragma once
#include "../models/ProductDAO.h"
#include <string>
#include <vector>

class ProductController {
private:
    ProductDAO productDAO;

public:
    std::vector<Product> getProducts();
    bool addProduct(const std::string& name, const std::string& description, 
                   double price, int stockQuantity);
    bool updateProduct(int id, const std::string& name, const std::string& description, 
                      double price, int stockQuantity);
    bool deleteProduct(int id);
    std::vector<Product> searchProducts(const std::string& query);
};