#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <string>
#include <cstdint>
#include "raylib.h"
#include "graphics/graphics.h"

class GameObject 
{
    protected:
        std::shared_ptr<Graphics> graphics_;
        u_int64_t uid_;

    public:
        std::string name;
        Rectangle position;

        GameObject(std::string const& name);
        ~GameObject();

        u_int64_t GetUid();
        int Add(std::shared_ptr<Graphics> graphic);
};

#endif