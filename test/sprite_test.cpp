#include <gtest/gtest.h>
#include "raylib.h"

#include "graphics/sprite.h"
#include "graphic_test.h"


class SpriteTest : public GraphicTest {
};

TEST_F(SpriteTest,TestLoadSprite) 
{

    Sprite new_sprite = Sprite();

    EXPECT_EQ(new_sprite.Load("testdata/Knight.png"), Graphics::OK);

    EXPECT_EQ(new_sprite.width,100);
    EXPECT_EQ(new_sprite.height,100); 

    int frame_counter = 0;
    bool exit_flag = false;
    SetTargetFPS(60);
    Vector2 position = {100,100};

    while (!WindowShouldClose() && !exit_flag)
    {
        frame_counter++;

        BeginDrawing();
        ClearBackground(BLACK);

        new_sprite.Draw(position);

        EndDrawing();

        // if (frame_counter >= this->delay_frames) 
        // {
        //     exit_flag = true;
        // }
    }
}