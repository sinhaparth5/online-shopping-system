#pragma once
#include <string>

class PasswordHasher {
public:
    static std::string hashPassword(const std::string& password);
    static bool verifyPassword(const std::string& password, const std::string& hashedPassword);
private:
    static std::string generateSalt();
};