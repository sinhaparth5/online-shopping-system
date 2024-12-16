#include "UserDAO.h"
#include "../config/database.h"
#include <sstream>

std::optional<User> UserDAO::getUserByUsername(const std::string& username) {
    sqlite3* db = Database::getInstance().getConnection();
    sqlite3_stmt* stmt;
    
    const char* query = "SELECT id, username, password_hash, email, address, is_admin "
                       "FROM users WHERE username = ?";
    
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            User user(
                sqlite3_column_int(stmt, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
                sqlite3_column_int(stmt, 5) != 0
            );
            sqlite3_finalize(stmt);
            return user;
        }
    }
    
    sqlite3_finalize(stmt);
    return std::nullopt;
}

bool UserDAO::addUser(const std::string& username, const std::string& password,
                     const std::string& email, const std::string& address) {
    sqlite3* db = Database::getInstance().getConnection();
    sqlite3_stmt* stmt;
    
    const char* query = "INSERT INTO users (username, password_hash, email, address) "
                       "VALUES (?, ?, ?, ?)";
    
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    
    std::string hashedPassword = PasswordHasher::hashPassword(password);
    
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, address.c_str(), -1, SQLITE_STATIC);
    
    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

bool UserDAO::verifyCredentials(const std::string& username, const std::string& password) {
    auto user = getUserByUsername(username);
    if (!user) {
        return false;
    }
    
    return PasswordHasher::verifyPassword(password, user->getPasswordHash());
}