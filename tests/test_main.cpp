#include <gtest/gtest.h>
#include "../src/config/database.h"

TEST(DatabaseTest, SingletonInstance) {
    Database& db1 = Database::getInstance();
    Database& db2 = Database::getInstance();
    
    // Both references should point to the same instance
    EXPECT_EQ(&db1, &db2);
}

TEST(DatabaseTest, ExecuteQuery) {
    Database& db = Database::getInstance();
    
    // Test creating a table
    EXPECT_NO_THROW({
        db.executeQuery(
            "CREATE TABLE IF NOT EXISTS test_table ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL)"
        );
    });
    
    // Test inserting data
    EXPECT_NO_THROW({
        db.executeQuery(
            "INSERT INTO test_table (name) VALUES ('test')"
        );
    });
}