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

using namespace Brutal;

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
    Level level = Level();

    auto gameobject = level.CreateGameObject("test");

    std::ifstream test_json("testdata/bbr.json");

    json parsed = json::parse(test_json);

    auto& bitmap = gameobject.AddComponent<BitmapComponent>(Bitmap::Deserialize(parsed));
    int frame_counter = 0;
    bool exit_flag = false;
    SetTargetFPS(60);
    Vector2 position = {100, 100};

    while (!WindowShouldClose() && !exit_flag) {
        frame_counter++;

        BeginDrawing();
        ClearBackground(BLACK);

        Bitmap::Draw(position, bitmap);

        EndDrawing();

        if (frame_counter >= this->delay_frames) {
            exit_flag = true;
        }
    }
}

TEST_F(GraphicTest, TestDrawSprite) {
    Level level = Level();

    std::ifstream test_json("testdata/player.json");

    json parsed = json::parse(test_json);

    auto gameobject = level.CreateGameObject("test");
    auto sprite_component = gameobject.AddComponent<SpriteComponent>(Sprite::Deserialize(parsed));

    int frame_counter = 0;
    bool exit_flag = false;
    SetTargetFPS(60);
    Vector2 position = {100, 100};

    while (!WindowShouldClose() && !exit_flag) {
        frame_counter++;

        BeginDrawing();
        ClearBackground(BLACK);

        Sprite::Draw(position, sprite_component);

        EndDrawing();

        if (frame_counter >= this->delay_frames) {
            exit_flag = true;
        }
    }
}