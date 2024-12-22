#include "App.h"
#include "utils/DatabaseInitializer.h"
#include <iostream>
#include <iomanip>
#include <limits>

void App::clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void App::displayMenu() {
    std::cout << "\n=== Product Management System ===\n"
              << "1. View all products\n"
              << "2. Add new product\n"
              << "3. Update product\n"
              << "4. Delete product\n"
              << "5. Search products\n"
              << "6. Update stock\n"
              << "0. Exit\n"
              << "Choose an option: ";
}

void App::displayProducts(const std::vector<Product>& products) {
    if (products.empty()) {
        std::cout << "No products found.\n";
        return;
    }

    std::cout << "\n=== Products List ===\n";
    std::cout << std::setw(5) << "ID" << " | "
              << std::setw(20) << "Name" << " | "
              << std::setw(30) << "Description" << " | "
              << std::setw(10) << "Price" << " | "
              << std::setw(10) << "Stock" << "\n";
    std::cout << std::string(80, '-') << "\n";

    for (const auto& product : products) {
        std::cout << std::setw(5) << product.getId() << " | "
                  << std::setw(20) << product.getName() << " | "
                  << std::setw(30) << product.getDescription() << " | "
                  << std::setw(10) << std::fixed << std::setprecision(2) << product.getPrice() << " | "
                  << std::setw(10) << product.getStockQuantity() << "\n";
    }
}

void App::addNewProduct(ProductController& controller) {
    std::string name, description;
    double price;
    int stock;

    std::cout << "\n=== Add New Product ===\n";
    
    std::cout << "Enter product name: ";
    clearInputStream();
    std::getline(std::cin, name);

    std::cout << "Enter product description: ";
    std::getline(std::cin, description);

    std::cout << "Enter price: ";
    while (!(std::cin >> price) || price < 0) {
        std::cout << "Invalid price. Please enter a positive number: ";
        clearInputStream();
    }

    std::cout << "Enter initial stock quantity: ";
    while (!(std::cin >> stock) || stock < 0) {
        std::cout << "Invalid quantity. Please enter a positive number: ";
        clearInputStream();
    }

    if (controller.addProduct(name, description, price, stock)) {
        std::cout << "Product added successfully!\n";
    } else {
        std::cout << "Failed to add product.\n";
    }
}

void App::updateProduct(ProductController& controller) {
    int id;
    std::cout << "\n=== Update Product ===\n";
    std::cout << "Enter product ID to update: ";
    while (!(std::cin >> id) || id <= 0) {
        std::cout << "Invalid ID. Please enter a positive number: ";
        clearInputStream();
    }

    auto product = controller.getProductById(id);
    if (!product) {
        std::cout << "Product not found.\n";
        return;
    }

    std::string name, description;
    double price;
    int stock;

    std::cout << "Current product details:\n";
    std::cout << "Name: " << product->getName() << "\n";
    std::cout << "Description: " << product->getDescription() << "\n";
    std::cout << "Price: " << product->getPrice() << "\n";
    std::cout << "Stock: " << product->getStockQuantity() << "\n\n";

    std::cout << "Enter new product name (or press Enter to keep current): ";
    clearInputStream();
    std::getline(std::cin, name);
    if (name.empty()) name = product->getName();

    std::cout << "Enter new description (or press Enter to keep current): ";
    std::getline(std::cin, description);
    if (description.empty()) description = product->getDescription();

    std::cout << "Enter new price (or -1 to keep current): ";
    std::cin >> price;
    if (price < 0) price = product->getPrice();

    std::cout << "Enter new stock quantity (or -1 to keep current): ";
    std::cin >> stock;
    if (stock < 0) stock = product->getStockQuantity();

    if (controller.updateProduct(id, name, description, price, stock)) {
        std::cout << "Product updated successfully!\n";
    } else {
        std::cout << "Failed to update product.\n";
    }
}

void App::deleteProduct(ProductController& controller) {
    int id;
    std::cout << "\n=== Delete Product ===\n";
    std::cout << "Enter product ID to delete: ";
    while (!(std::cin >> id) || id <= 0) {
        std::cout << "Invalid ID. Please enter a positive number: ";
        clearInputStream();
    }

    if (controller.deleteProduct(id)) {
        std::cout << "Product deleted successfully!\n";
    } else {
        std::cout << "Failed to delete product.\n";
    }
}

void App::searchProducts(ProductController& controller) {
    std::string query;
    std::cout << "\n=== Search Products ===\n";
    std::cout << "Enter search term: ";
    clearInputStream();
    std::getline(std::cin, query);

    auto products = controller.searchProducts(query);
    displayProducts(products);
}

void App::updateStock(ProductController& controller) {
    int id, quantity;
    std::cout << "\n=== Update Stock ===\n";
    std::cout << "Enter product ID: ";
    while (!(std::cin >> id) || id <= 0) {
        std::cout << "Invalid ID. Please enter a positive number: ";
        clearInputStream();
    }

    std::cout << "Enter quantity change (positive to add, negative to subtract): ";
    while (!(std::cin >> quantity)) {
        std::cout << "Invalid quantity. Please enter a number: ";
        clearInputStream();
    }

    if (controller.updateStock(id, quantity)) {
        std::cout << "Stock updated successfully!\n";
    } else {
        std::cout << "Failed to update stock.\n";
    }
}

void App::run() {
    try {
        DatabaseInitializer::initializeDatabase();
        ProductController productController;
        
        int choice;
        do {
            displayMenu();
            std::cin >> choice;

            switch (choice) {
                case 1:
                    displayProducts(productController.getProducts());
                    break;
                case 2:
                    addNewProduct(productController);
                    break;
                case 3:
                    updateProduct(productController);
                    break;
                case 4:
                    deleteProduct(productController);
                    break;
                case 5:
                    searchProducts(productController);
                    break;
                case 6:
                    updateStock(productController);
                    break;
                case 0:
                    std::cout << "Goodbye!\n";
                    break;
                default:
                    std::cout << "Invalid option. Please try again.\n";
            }
        } while (choice != 0);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}