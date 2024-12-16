#include "User.h"

User::User(int id, std::string username, std::string passwordHash, 
           std::string email, std::string address, bool isAdmin)
    : id(id), username(std::move(username)), passwordHash(std::move(passwordHash)),
      email(std::move(email)), address(std::move(address)), isAdmin(isAdmin) {}