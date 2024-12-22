#include <gtest/gtest.h>
#include "utils/DatabaseInitializer.h"

class GlobalTestEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        try {
            DatabaseInitializer::initializeDatabase();
        } catch (const std::exception& e) {
            std::cerr << "Test environment setup failed: " << e.what() << std::endl;
            throw;
        }
    }
};

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment(new GlobalTestEnvironment);
    return RUN_ALL_TESTS();
}