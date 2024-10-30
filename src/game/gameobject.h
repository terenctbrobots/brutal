#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <string>
#include "raylib.h"
#include "graphics/graphics.h"

class GameObject 
{
    protected:
        std::shared_ptr<Graphics> graphics_;

    public:
        std::string name;
        Rectangle position;

        GameObject();
        ~GameObject();

        int Add(std::shared_ptr<Graphics> graphic);
};

#endif