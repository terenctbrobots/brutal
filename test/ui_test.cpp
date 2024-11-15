#include <fstream>

#include "game/gameobject.h"
#include "game/level.h"
#include "graphic_test.h"
#include "raylib.h"
#include "ui/button.h"
#include "ui/text.h"

using namespace Brutal;

TEST_F(GraphicTest, TestUI) {
    Level level = Level();

    auto gameobject = level.CreateGameObject("test");

    std::ifstream text_json("testdata/text.json");

    json text_parsed = json::parse(text_json);

    auto& text = gameobject.AddComponent<TextComponent>(Text::Deserialize(text_parsed));

    std::ifstream button_json("testdata/button.json");
    json button_parsed = json::parse(button_json);

    auto& button = gameobject.AddComponent<ButtonComponent>(Button::Deserialize(button_parsed));
    int frame_counter = 0;
    bool exit_flag = false;
    SetTargetFPS(60);
    Vector2 position = {100, 100};

    while (!WindowShouldClose() && !exit_flag) {
        frame_counter++;

        BeginDrawing();
        ClearBackground(BLACK);

        Text::Draw(position, text);
        Button::Draw({100, 200}, button,0);

        EndDrawing();

        if (frame_counter >= this->delay_frames) {
            exit_flag = true;
        }
    }
}
