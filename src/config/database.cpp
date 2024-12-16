#include "database.h"
#include <iostream>

std::unique_ptr<Database> Database::instance = nullptr;
std::mutex Database::mutex;

Database::Database(const std::string& dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        std::string error = sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error("Cannot open database: " + error);
    }
}

Database& Database::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!instance) {
        instance = std::unique_ptr<Database>(new Database("shop.db"));
    }
    return *instance;
}

void Database::executeQuery(const std::string& query) {
    std::lock_guard<std::mutex> lock(mutex);
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::string error = errMsg;
        sqlite3_free(errMsg);
        throw std::runtime_error("SQL error: " + error);
    }
}

Database::~Database() {
    std::lock_guard<std::mutex> lock(mutex);
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}