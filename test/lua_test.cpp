
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

class Greeter : public std::enable_shared_from_this<Greeter> {
   public:
    Greeter(const std::string_view name) : m_name(name) {}

    std::string getName() const { return m_name; }

    void printName() { std::cout << "[C++ CODE] Hello, my name is " << m_name << "!" << std::endl; }

   private:
    std::string m_name;
};

class GreeterSelector {
   public:
    GreeterSelector() {
        greet1_ = std::make_shared<Greeter>("greet 1");
        greet2_ = std::make_shared<Greeter>("greet 2");
    }

    std::shared_ptr<Greeter> GetGreeter(int which) {
        if (which == 1) return greet1_;

        return greet2_;
    }

   private:
    std::shared_ptr<Greeter> greet1_;
    std::shared_ptr<Greeter> greet2_;
};

TEST(LuaTest, TestLuaBridge) {
    lua_State* luaState = luaL_newstate();

    // load standard libs
    luaL_openlibs(luaState);

    luabridge::getGlobalNamespace(luaState)
        .beginClass<Greeter>("Greeter")
        .addFunction("getName", &Greeter::getName)
        .endClass();

    luabridge::getGlobalNamespace(luaState)
        .beginClass<GreeterSelector>("GreeterSelector")
        .addFunction("getGreeter", &GreeterSelector::GetGreeter)
        .endClass();

    auto globalGreeterSelection = std::make_unique<GreeterSelector>();
    luabridge::setGlobal(luaState, globalGreeterSelection.get(), "greeterselect");

    luaL_dofile(luaState, "testdata/instance.lua");
}
}  // namespace
