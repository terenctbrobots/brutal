#include "level.h"


Level::Level()
{
    render_layers_.push_back(std::make_unique<Layer>());
}

Level::~Level()
{

}


int Level::MainLoop()
{
    #ifdef DEBUG
    char* delay_string = std::getenv("DELAY");
    int delay_frames = 5;

    if (delay_string != NULL) 
    {
        delay_frames =  atoi(delay_string);
    } 
    int frame_counter = 0;
    bool exit_flag = false;
    #endif
    SetTargetFPS(60);

#ifdef DEBUG
    while (!WindowShouldClose() && !exit_flag)
#else 
    while (!WindowShouldClose())
#endif   
    {

        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();

#ifdef DEBUG
        frame_counter++;

        if (frame_counter >= delay_frames) 
        {
            exit_flag = true;
        }
#endif
    }

    return 0;
}