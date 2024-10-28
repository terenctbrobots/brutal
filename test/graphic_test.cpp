#include <cstdlib>
#include "raylib.h"
#include "graphic_test.h"
#include "graphics/sprite.h"
#include "graphics/tileset.h"


void GraphicTest::SetUp() {

    char* delay_string = std::getenv("DELAY");

    if (delay_string != NULL) 
    {
        delay_frames =  atoi(delay_string);
    } 

    InitWindow(800,600,"Graphic Test");
}

void GraphicTest::TearDown() {
    CloseWindow();
}

class SpriteTest : public GraphicTest {
};

TEST_F(SpriteTest, TestLoadTileSet) 
{
    TileSet new_tileset = TileSet();

    EXPECT_EQ(new_tileset.Load("testdata/plains.png"), Graphics::OK);

    int frame_counter = 0;
    bool exit_flag = false;
    SetTargetFPS(60);

    while (!WindowShouldClose() && !exit_flag)
    {
        frame_counter++;

        BeginDrawing();
        ClearBackground(BLACK);

        new_tileset.Draw({100,100},1);

        EndDrawing();

        if (frame_counter >= this->delay_frames) 
        {
            exit_flag = true;
        }
    }

}

TEST_F(SpriteTest,TestLoadSprite) 
{

    Sprite new_sprite = Sprite();

    EXPECT_EQ(new_sprite.Load("testdata/player.png"), Graphics::OK);

    EXPECT_EQ(new_sprite.width,48);
    EXPECT_EQ(new_sprite.height,48); 

    new_sprite.SetAnimation("moveLeftRight");
    new_sprite.FlipX();

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

        if (frame_counter >= this->delay_frames) 
        {
            exit_flag = true;
        }
    }
}