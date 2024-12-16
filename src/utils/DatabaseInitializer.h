#pragma once
#include "../config/database.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

class DatabaseInitializer {
public:
    static void initializeDatabase();
    static void seedDatabase(); // Add sample data for testing

private:
    static std::vector<std::string> readSQLFile(const std::string& filename);
    static void executeSQL(const std::string& sql);
    static bool tableExists(const std::string& tableName);
};