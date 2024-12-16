#pragma once
#include "../models/Product.h"
#include "../models/ProductDAO.h"
#include <string>
#include <vector>
#include <optional>

class ProductController {
private:
    ProductDAO productDAO;

public:
    // Get all products
    std::vector<Product> getProducts();
    
    // Get a single product by ID
    std::optional<Product> getProductById(int id);
    
    // Add a new product
    bool addProduct(const std::string& name, const std::string& description, 
                   double price, int stockQuantity);
    
    // Update an existing product
    bool updateProduct(int id, const std::string& name, const std::string& description, 
                      double price, int stockQuantity);
    
    // Delete a product
    bool deleteProduct(int id);
    
    // Search products
    std::vector<Product> searchProducts(const std::string& query);
    
    // Update product stock
    bool updateStock(int id, int quantity);
};