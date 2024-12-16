#pragma once
#include <sqlite3.h>
#include <string>
#include <memory>
#include <stdexcept>

class Database {
private:
    sqlite3* db;
    static std::unique_ptr<Database> instance;
    
    Database(const std::string& dbPath);
    
    // Prevent copying
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

public:
    static Database& getInstance();
    sqlite3* getConnection() { return db; }
    void executeQuery(const std::string& query);
    ~Database();
};