#include "ProductDAO.h"
#include "../config/database.h"
#include <sstream>

std::vector<Product> ProductDAO::getAllProducts() {
    std::vector<Product> products;
    sqlite3* db = Database::getInstance().getConnection();
    sqlite3_stmt* stmt;

    const char* query = "SELECT id, name, description, price, stock_quantity FROM products";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            products.emplace_back(
                sqlite3_column_int(stmt, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                sqlite3_column_double(stmt, 3),
                sqlite3_column_int(stmt, 4)
            );
        }
    }

    sqlite3_finalize(stmt);
    return products;
}

void ProductDAO::addProduct(const Product& product) {
    sqlite3* db = Database::getInstance().getConnection();
    sqlite3_stmt* stmt;
    
    const char* query = "INSERT INTO products (name, description, price, stock_quantity) VALUES (?, ?, ?, ?)";
    
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement");
    }
    
    sqlite3_bind_text(stmt, 1, product.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, product.getDescription().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, product.getPrice());
    sqlite3_bind_int(stmt, 4, product.getStockQuantity());
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to add product");
    }
    
    sqlite3_finalize(stmt);
}