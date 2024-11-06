#include "graphic_test.h"
#include "raylib.h"

TEST_F(GraphicTest, TestUI) {
    int frame_counter = 0;
    bool exit_flag = false;
    SetTargetFPS(60);

    while (!WindowShouldClose() && !exit_flag) {
        frame_counter++;

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Hello World", 100, 100, 20, WHITE);

        EndDrawing();

        if (frame_counter >= this->delay_frames) {
            exit_flag = true;
        }
    }
}
