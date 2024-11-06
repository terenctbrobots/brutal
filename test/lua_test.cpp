
#include <gtest/gtest.h>

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

namespace {
TEST(LuaTest, TestBasicLua) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "testdata/test.lua");
}
}  // namespace
