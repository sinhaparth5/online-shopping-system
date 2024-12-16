#include "ProductDAO.h"
#include <sstream>

// ... [Previous implementations remain the same]

std::vector<Product> ProductDAO::searchProducts(const std::string& searchTerm) {
    std::vector<Product> products;
    sqlite3* db = Database::getInstance().getConnection();
    sqlite3_stmt* stmt;
    
    const char* query = "SELECT id, name, description, price, stock_quantity FROM products "
                       "WHERE name LIKE ? OR description LIKE ?";
    
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        std::string searchPattern = "%" + searchTerm + "%";
        sqlite3_bind_text(stmt, 1, searchPattern.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, searchPattern.c_str(), -1, SQLITE_STATIC);
        
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