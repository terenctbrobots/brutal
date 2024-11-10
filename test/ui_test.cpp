#include "graphic_test.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include <fstream>

#include "game/gameobject.h"
#include "game/level.h"
#include "raygui.h"
#include "ui/button.h"
#include "ui/text.h"

using namespace Brutal;

TEST_F(GraphicTest, TestUI) {
    // Level level = Level();

    // auto gameobject = level.CreateGameObject("test");

    // std::ifstream text_json("testdata/text.json");

    // json parsed = json::parse(text_json);

    // auto& text = gameobject.AddComponent<TextComponent>(Text::Deserialize(parsed));
    // int frame_counter = 0;
    // bool exit_flag = false;
    // SetTargetFPS(60);
    // Vector2 position = {100, 100};

    // while (!WindowShouldClose() && !exit_flag) {
    //     frame_counter++;

    //     BeginDrawing();
    //     ClearBackground(BLACK);

    //     Text::Draw(position, text);

    //     EndDrawing();

    //     if (frame_counter >= this->delay_frames) {
    //         exit_flag = true;
    //     }
    // }
}
