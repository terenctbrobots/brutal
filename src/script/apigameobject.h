#pragma once

#include "game/gameobject.h"
#include <string>

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

namespace Brutal 
{
class APIGameObject {
    public:
        entt::entity entity_;
    public:
        void Bind(lua_State* L);
        void setText(std::string const& text);
};
}

