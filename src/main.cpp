#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
#ifdef DEBUG            
            DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
#endif
        EndDrawing();
    }

    CloseWindow();

    return 0;
}