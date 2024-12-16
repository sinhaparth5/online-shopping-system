#include "database.h"
#include <iostream>

std::unique_ptr<Database> Database::instance = nullptr;

Database::Database(const std::string& dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        std::string error = sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error("Cannot open database: " + error);
    }
}

Database& Database::getInstance() {
    if (!instance) {
        instance = std::make_unique<Database>("shop.db");
    }
    return *instance;
}

void Database::executeQuery(const std::string& query) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::string error = errMsg;
        sqlite3_free(errMsg);
        throw std::runtime_error("SQL error: " + error);
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}