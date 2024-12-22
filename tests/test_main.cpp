#include <gtest/gtest.h>
#include "../src/controllers/ProductController.h"
#include "../src/utils/DatabaseInitializer.h"

class ProductTest : public ::testing::Test {
protected:
    void SetUp() override {
        DatabaseInitializer::initializeDatabase();
    }
    
    ProductController controller;
};

TEST_F(ProductTest, AddProduct) {
    bool result = controller.addProduct("Test Product", "Test Description", 99.99, 10);
    EXPECT_TRUE(result);
    
    auto products = controller.getProducts();
    EXPECT_FALSE(products.empty());
}

TEST_F(ProductTest, GetProducts) {
    auto products = controller.getProducts();
    EXPECT_NO_THROW(products);
}

TEST_F(ProductTest, DeleteProduct) {
    // First add a product
    controller.addProduct("Delete Test", "Test Description", 99.99, 10);
    auto products = controller.getProducts();
    ASSERT_FALSE(products.empty());
    
    // Then delete it
    bool result = controller.deleteProduct(products[0].getId());
    EXPECT_TRUE(result);
}

// Add more tests as needed