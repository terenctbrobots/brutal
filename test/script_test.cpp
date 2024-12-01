
#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <string_view>

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include <luabridge3/LuaBridge/LuaBridge.h>

#include "game/game.h"
#include "helper.h"
#include "script/scriptcore.h"

using namespace Brutal;

namespace
{
TEST(ScriptTest, TestPreprocessor)
{
    ScriptCore script_core = ScriptCore();

    std::string function_name = script_core.FormatFunction({1, 1});

    EXPECT_EQ(function_name, "_1_onTick");

    std::optional<std::string> script_buffer = script_core.PreProcessScript("./testdata/preprocess_pre.lua", 1);

    EXPECT_TRUE(script_buffer.has_value());

    std::optional<std::string> valid_buffer = LoadTextFile("./testdata/preprocess_post.lua");

    EXPECT_TRUE(valid_buffer.has_value());

    EXPECT_EQ(*script_buffer, *valid_buffer);
}

TEST(ScriptTest, TestScriptCore)
{
    Game& game = Game::Get();

    game.Setup(640, 480);

    game.CreateLevel();

    std::ifstream test_json("testdata/scripttest.json");

    json json_data = json::parse(test_json);

    game.level->Deserialize(json_data);

    game.MainLoop();

    game.Cleanup();
}
}  // namespace