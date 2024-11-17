#pragma once

#include <string>
#include "apigameobject.h"
extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

namespace Brutal {
class APIGlobal {
    private:
static        APIGameObject api_;
    friend APIGlobal;
    public:
    static void Bind(lua_State* L);
    static APIGameObject& findGameObjectByName(std::string const& name);
};
}
