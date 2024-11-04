#include <iostream>
#include "level.h"
#include "graphics/objectlayer.h"

Level::Level()
{
    render_layers_.push_back(std::make_shared<ObjectLayer>());
}

Level::~Level()
{

}

int Level::Add(std::shared_ptr<GameObject> gameobject, u_int32_t layer)
{
    auto render_layer = render_layers_[layer];

    if (render_layer->GetLayerType() == Layer::OBJECT)
    {
        std::static_pointer_cast<ObjectLayer>(render_layer)->Add(gameobject);
    }

    return 0;
}

int Level::LoadSprite(std::string const& file_name, u_int32_t layer) 
{
    auto gameobject = std::make_shared<GameObject>("sprite");
    gameobject->LoadSprite(file_name);
    Add(gameobject, layer);

    return 0;
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
        for (auto olayer=render_layers_.begin(); olayer != render_layers_.end(); olayer++)
        {
            if ((*olayer)->enabled) {
                (*olayer)->OrganizeDraw();
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (auto rlayer=render_layers_.begin(); rlayer != render_layers_.end(); rlayer++)
        {
            if ((*rlayer)->enabled) {
                (*rlayer)->Draw();
            }
        }

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