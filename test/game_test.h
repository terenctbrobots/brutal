#include <gtest/gtest.h>

class GameTest : public testing::Test {
    public:
        int delay_frames = 5;
    protected:
        void SetUp() override {}
        void TearDown() override {};
};