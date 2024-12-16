#pragma once
#include "../models/UserDAO.h"
#include <string>
#include <optional>

class UserController {
private:
    UserDAO userDAO;

public:
    bool registerUser(const std::string& username, const std::string& password,
                     const std::string& email, const std::string& address);
    bool loginUser(const std::string& username, const std::string& password);
    std::optional<User> getUserProfile(const std::string& username);
    bool updateUserProfile(const std::string& username, const std::string& email,
                         const std::string& address);
    bool changePassword(const std::string& username, const std::string& oldPassword,
                       const std::string& newPassword);
};