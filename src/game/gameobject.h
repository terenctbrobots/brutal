#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <cstdint>
#include <memory>
#include <string>

#include "raylib.h"
#include "render.h"

class GameObject {
   protected:
    // TODO: Make this a unique_ptr, once we can serialize it
    std::shared_ptr<Render> render_;
    u_int64_t uid_;

   public:
    std::string name;
    Rectangle position;
    bool enabled = true;

    GameObject(std::string const& name);
    ~GameObject();

    u_int64_t GetUid();

    int LoadSprite(std::string const& file_name);
    void Draw();
};

#endif