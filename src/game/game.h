#ifndef GAME_H
#define GAME_H
#include <memory>
#include <cstdint>
#include "raylib.h"
#include "level.h"

class Game 
{
    public:
        Rectangle view_screen;
        std::shared_ptr<Level> level; 

        Game(float width, float height);
        ~Game();

        // This is usually for internal use, probably use LoadLevel to serialize from json file
        std::shared_ptr<Level> CreateLevel(std::shared_ptr<Level> new_level);
        int MainLoop();
};

#endif