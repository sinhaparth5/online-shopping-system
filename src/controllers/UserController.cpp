#include "UserController.h"

bool UserController::registerUser(const std::string& username, const std::string& password,
                                const std::string& email, const std::string& address) {
    if (username.empty() || password.empty() || email.empty()) {
        return false;
    }
    
    return userDAO.addUser(username, password, email, address);
}

bool UserController::loginUser(const std::string& username, const std::string& password) {
    return userDAO.verifyCredentials(username, password);
}