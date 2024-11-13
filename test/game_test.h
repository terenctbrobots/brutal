#include <gtest/gtest.h>

#include "raylib.h"

class GameTest : public testing::Test {
   public:
    int delay_frames = 5;

   protected:
    void SetUp() override { SetTraceLogLevel(LOG_ERROR); }
    void TearDown() override {};
};