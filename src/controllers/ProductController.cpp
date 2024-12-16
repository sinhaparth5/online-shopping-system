#include "ProductController.h"
#include <iostream>
#include <sstream>

std::vector<Product> ProductController::getProducts() {
    try {
        return productDAO.getAllProducts();
    } catch (const std::exception& e) {
        std::cerr << "Error getting products: " << e.what() << std::endl;
        return std::vector<Product>();
    }
}

bool ProductController::addProduct(const std::string& name, const std::string& description, 
                                 double price, int stockQuantity) {
    if (name.empty() || price < 0 || stockQuantity < 0) {
        return false;
    }

    try {
        Product newProduct(0, name, description, price, stockQuantity);
        productDAO.addProduct(newProduct);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error adding product: " << e.what() << std::endl;
        return false;
    }
}

bool ProductController::updateProduct(int id, const std::string& name, const std::string& description, 
                                    double price, int stockQuantity) {
    if (id <= 0 || name.empty() || price < 0 || stockQuantity < 0) {
        return false;
    }

    try {
        auto existingProduct = productDAO.getProductById(id);
        if (!existingProduct) {
            return false;
        }

        Product updatedProduct(id, name, description, price, stockQuantity);
        productDAO.updateProduct(updatedProduct);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error updating product: " << e.what() << std::endl;
        return false;
    }
}

bool ProductController::deleteProduct(int id) {
    if (id <= 0) {
        return false;
    }

    try {
        productDAO.deleteProduct(id);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error deleting product: " << e.what() << std::endl;
        return false;
    }
}

std::vector<Product> ProductController::searchProducts(const std::string& query) {
    if (query.empty()) {
        return getProducts();
    }

    try {
        return productDAO.getAllProducts(); // For now, return all products
    } catch (const std::exception& e) {
        std::cerr << "Error searching products: " << e.what() << std::endl;
        return std::vector<Product>();
    }
}

std::optional<Product> ProductController::getProductById(int id) {
    if (id <= 0) {
        return std::nullopt;
    }

    try {
        return productDAO.getProductById(id);
    } catch (const std::exception& e) {
        std::cerr << "Error getting product: " << e.what() << std::endl;
        return std::nullopt;
    }
}

bool ProductController::updateStock(int id, int quantity) {
    if (id <= 0) {
        return false;
    }

    try {
        auto product = productDAO.getProductById(id);
        if (!product) {
            return false;
        }

        int newQuantity = product->getStockQuantity() + quantity;
        if (newQuantity < 0) {
            return false;
        }

        Product updatedProduct(id, product->getName(), product->getDescription(),
                             product->getPrice(), newQuantity);
        productDAO.updateProduct(updatedProduct);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error updating stock: " << e.what() << std::endl;
        return false;
    }
}