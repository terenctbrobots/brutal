#include "graphic_test.h"

#include <cstdlib>
#include <fstream>

#include "game/gameobject.h"
#include "game/level.h"
#include "graphics/bitmap.h"
#include "graphics/sprite.h"
#include "graphics/tilelayer.h"
#include "graphics/tileset.h"
#include "graphics/tilesetpack.h"
#include "raylib.h"

void GraphicTest::SetUp() {
    SetTraceLogLevel(LOG_ERROR);

    char* delay_string = std::getenv("DELAY");

    if (delay_string != NULL) {
        delay_frames = atoi(delay_string);
    }

    InitWindow(800, 600, "Graphic Test");
}

void GraphicTest::TearDown() { CloseWindow(); }

TEST_F(GraphicTest, TestLoadTileSet) {
    // TileSet new_tileset = TileSet();

    // EXPECT_EQ(new_tileset.Load("testdata/plains.png"), Render::OK);

    // int frame_counter = 0;
    // bool exit_flag = false;
    // SetTargetFPS(60);

    // while (!WindowShouldClose() && !exit_flag) {
    //     frame_counter++;

    //     BeginDrawing();
    //     ClearBackground(BLACK);

    //     new_tileset.Draw({100, 100}, 1);

    //     EndDrawing();

    //     if (frame_counter >= this->delay_frames) {
    //         exit_flag = true;
    //     }
    // }
}

TEST_F(GraphicTest, TestDrawBitmap) {
    // Bitmap new_bitmap = Bitmap();
    // EXPECT_EQ(new_bitmap.Load("testdata/bbr.png"), Render::OK);

    // int frame_counter = 0;
    // bool exit_flag = false;
    // SetTargetFPS(60);

    // while (!WindowShouldClose() && !exit_flag) {
    //     frame_counter++;

    //     BeginDrawing();
    //     ClearBackground(BLACK);

    //     new_bitmap.Draw({100, 100});

    //     EndDrawing();

    //     if (frame_counter >= this->delay_frames) {
    //         exit_flag = true;
    //     }
    // }
}

TEST_F(GraphicTest, TestDrawSprite) {
    Level level = Level();

    auto gameobject = level.CreateGameObject("test");
    auto sprite_component = gameobject.AddComponent<SpriteComponent>();

    std::ifstream test_json("testdata/player.json");

    json parsed = json::parse(test_json);

    Sprite::Deserialize(sprite_component, gameobject, parsed);
    // Sprite new_sprite = Sprite();

    // EXPECT_EQ(new_sprite.Load("testdata/player.png"), Render::OK);

    // EXPECT_EQ(new_sprite.width, 48);
    // EXPECT_EQ(new_sprite.height, 48);

    // new_sprite.SetAnimation("moveLeftRight");
    // new_sprite.FlipX();

    // int frame_counter = 0;
    // bool exit_flag = false;
    // SetTargetFPS(60);
    // Vector2 position = {100, 100};

    // while (!WindowShouldClose() && !exit_flag) {
    //     frame_counter++;

    //     BeginDrawing();
    //     ClearBackground(BLACK);

    //     new_sprite.Draw(position);

    //     EndDrawing();

    //     if (frame_counter >= this->delay_frames) {
    //         exit_flag = true;
    //     }
    // }
}