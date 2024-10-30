#include "level.h"


Level::Level()
{

}

Level::~Level()
{

}


int Level::MainLoop()
{
    int frame_counter = 0;
    bool exit_flag = false;
    SetTargetFPS(60);

    while (!WindowShouldClose() && !exit_flag)
    {
        frame_counter++;

        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();

        if (frame_counter >= 200) 
        {
            exit_flag = true;
        }
    }

    return 0;
}