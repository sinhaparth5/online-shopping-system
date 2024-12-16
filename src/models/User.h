#pragma once
#include <string>
#include <vector>

class User {
private:
    int id;
    std::string username;
    std::string passwordHash;
    std::string email;
    std::string address;
    bool isAdmin;

public:
    User(int id, std::string username, std::string passwordHash, 
         std::string email, std::string address, bool isAdmin = false);
    
    // Getters
    int getId() const { return id; }
    std::string getUsername() const { return username; }
    std::string getPasswordHash() const { return passwordHash; }  // Added getter for passwordHash
    std::string getEmail() const { return email; }
    std::string getAddress() const { return address; }
    bool getIsAdmin() const { return isAdmin; }
    
    // Setters
    void setEmail(const std::string& newEmail) { email = newEmail; }
    void setAddress(const std::string& newAddress) { address = newAddress; }
};