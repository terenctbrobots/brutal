
#include <gtest/gtest.h>

#include <iostream>
#include <memory>
#include <string_view>

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include <luabridge3/LuaBridge/LuaBridge.h>

namespace {
TEST(LuaTest, TestBasicLua) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "testdata/test.lua");
}

class APIGame {
   public:
    int entity;
    void setText(std::string const& text) {
        std::cout << entity << ":" << text << std::endl;
    }
};

static APIGame api = APIGame();

class APIGlobal {
    public:
static APIGame& findGameObjectByName(std::string const& name) {
    std::cout << name << std::endl;

    if (name == "test1") {
        api.entity = 1;
    } else if (name == "test2") {
        api.entity = 2;
    }

    return api;
}

};

TEST(LuaTest, TestLuaBridge) {
    lua_State* luaState = luaL_newstate();

    // load standard libs
    luaL_openlibs(luaState);

    luabridge::getGlobalNamespace(luaState)
        .beginClass<APIGame>("APIGame")
        .addFunction("setText", &APIGame::setText)
        .endClass();

    // luabridge::getGlobalNamespace(luaState)
    //     .beginClass<GreeterSelector>("GreeterSelector")
    //     .addFunction("getGreeter", &GreeterSelector::GetGreeter)
    //     .endClass();

    // auto globalGreeterSelection = std::make_unique<GreeterSelector>();
    // luabridge::setGlobal(luaState, globalGreeterSelection.get(), "greeterselect");

    luabridge::getGlobalNamespace(luaState)
        .addFunction("findGameObjectByName",&APIGlobal::findGameObjectByName);

    luaL_dofile(luaState, "testdata/instance.lua");
}
}  // namespace
