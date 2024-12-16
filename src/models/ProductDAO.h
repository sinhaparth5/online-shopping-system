#pragma once
#include "Product.h"
#include <vector>
#include <optional>

class ProductDAO {
    public:
    std::vector<Product> getAllProducts();
    std::optional<Product> getProductById(int id);
    void addProduct(const Product& product);
    void updateProduct(const Product& product);
    void deleteProduct(int id);
    std::vector<Product> searchProduct(const std::string& query);
};