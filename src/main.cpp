#include "config/database.h"
#include "controllers/ProductController.h"
#include "utils/DatabaseInitializer.h"
#include <iostream>

int main() {
    try {
        // Initialize database
        DatabaseInitializer::initializeDatabase();
        
        // Create controller
        ProductController productController;
        
        // Add sample product
        productController.addProduct("Laptop", "High-performance laptop", 999.99, 10);
        
        // Get all products
        auto products = productController.getProducts();
        
        // Display products
        for (const auto& product : products) {
            std::cout << "Product: " << product.getName() 
                     << ", Price: $" << product.getPrice() 
                     << ", Stock: " << product.getStockQuantity() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}