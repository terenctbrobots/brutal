#ifndef LAYER_H
#define LAYER_H

#include <string>
#include "raylib.h"
#include "graphics.h"

class Layer 
{
    public:
        uint32_t layer = 0;

        Layer();
        ~Layer();

        int Draw();
    
};
#endif