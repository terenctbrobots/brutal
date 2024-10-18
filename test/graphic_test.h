#include <gtest/gtest.h>

class GraphicTest : public testing::Test {
    protected:
        void SetUp() override {
            std::cout << "Setup" << std::endl;
        }

        void TearDown() override {
            std::cout << "Teardown" << std::endl;
        }
};