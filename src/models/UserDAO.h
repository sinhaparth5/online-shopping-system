#pragma once
#include "User.h"
#include <optional>
#include <vector>

class UserDAO {
public:
    std::optional<User> getUserById(int id);
    std::optional<User> getUserByUsername(const std::string& username);
    std::optional<User> getUserByEmail(const std::string& email);
    std::vector<User> getAllUsers();
    bool addUser(const std::string& username, const std::string& password,
                const std::string& email, const std::string& address);
    bool updateUser(const User& user);
    bool deleteUser(int id);
    bool verifyCredentials(const std::string& username, const std::string& password);
};
