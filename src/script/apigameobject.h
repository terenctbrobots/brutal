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
        entt::entity m_Entity;
    public:
        void Bind(lua_State* L);
        void SetText(std::string const& text);
        void SetPosition(float x, float y);
};
}

