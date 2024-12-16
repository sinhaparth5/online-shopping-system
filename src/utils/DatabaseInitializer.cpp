// src/utils/DatabaseInitializer.cpp
#include "DatabaseInitializer.h"
#include <iostream>

void DatabaseInitializer::initializeDatabase() {
    try {
        // Read and execute schema.sql
        auto sqlStatements = readSQLFile("sql/schema.sql");
        
        for (const auto& sql : sqlStatements) {
            if (!sql.empty()) {
                executeSQL(sql);
            }
        }
        
        // Seed database with initial data if tables are empty
        if (!tableExists("users") || !tableExists("products")) {
            seedDatabase();
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Database initialization failed: " + std::string(e.what()));
    }
}

std::vector<std::string> DatabaseInitializer::readSQLFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open SQL file: " + filename);
    }

    std::vector<std::string> statements;
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    // Split the content into separate SQL statements
    size_t pos = 0;
    std::string statement;
    while ((pos = content.find(';')) != std::string::npos) {
        statement = content.substr(0, pos);
        if (!statement.empty() && statement.find_first_not_of(" \t\n\r") != std::string::npos) {
            statements.push_back(statement);
        }
        content.erase(0, pos + 1);
    }

    return statements;
}

void DatabaseInitializer::executeSQL(const std::string& sql) {
    Database::getInstance().executeQuery(sql);
}

bool DatabaseInitializer::tableExists(const std::string& tableName) {
    sqlite3* db = Database::getInstance().getConnection();
    sqlite3_stmt* stmt;
    
    std::string query = "SELECT count(*) FROM sqlite_master WHERE type='table' AND name=?";
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, tableName.c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            return count > 0;
        }
    }
    
    sqlite3_finalize(stmt);
    return false;
}

void DatabaseInitializer::seedDatabase() {
    // Add sample admin user
    executeSQL("INSERT INTO users (username, password_hash, email, is_admin) "
              "VALUES ('admin', '$2y$10$seedhash', 'admin@example.com', 1)");
    
    // Add sample products
    std::vector<std::string> sampleProducts = {
        "INSERT INTO products (name, description, price, stock_quantity) "
        "VALUES ('Laptop', 'High-performance gaming laptop', 999.99, 10)",
        
        "INSERT INTO products (name, description, price, stock_quantity) "
        "VALUES ('Smartphone', 'Latest model smartphone', 699.99, 20)",
        
        "INSERT INTO products (name, description, price, stock_quantity) "
        "VALUES ('Headphones', 'Wireless noise-canceling headphones', 199.99, 30)"
    };
    
    for (const auto& sql : sampleProducts) {
        executeSQL(sql);
    }
}