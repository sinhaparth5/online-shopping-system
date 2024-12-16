#pragma once
#include "Product.h"
#include "../config/database.h"
#include <vector>
#include <optional>
#include <string>

class ProductDAO {
public:
    // Get all products
    std::vector<Product> getAllProducts();
    
    // Get a single product by ID
    std::optional<Product> getProductById(int id);
    
    // Add a new product
    void addProduct(const Product& product);
    
    // Update an existing product
    void updateProduct(const Product& product);
    
    // Delete a product
    void deleteProduct(int id);
    
    // Search products by name or description
    std::vector<Product> searchProducts(const std::string& searchTerm);
};