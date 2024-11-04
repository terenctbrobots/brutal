#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <vector>
#include <memory>
#include "raylib.h"
#include "game/level.h"



class Layer 
{
    protected:
        int layer_type_;
    public:
        enum LayerType 
        {
            BASE = 0,
            OBJECT,
            TILE
        };

        bool enabled = true;
        
        Layer() {};
        ~Layer() {};

        int GetLayerType() { return layer_type_; }

        virtual void OrganizeDraw() = 0;
        virtual void Draw() = 0;
};
#endif