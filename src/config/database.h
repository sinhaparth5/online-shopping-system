#pragma once
#include <sqlite3.h>
#include <string>
#include <memory>
#include <mutex>
#include <stdexcept>

class Database {
private:
    sqlite3* db;
    static std::unique_ptr<Database> instance;
    static std::mutex mutex;
    
    friend std::unique_ptr<Database>;

public:
    Database(const std::string& dbPath);
    static Database& getInstance();
    sqlite3* getConnection() { return db; }
    void executeQuery(const std::string& query);
    ~Database();
    
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
};
