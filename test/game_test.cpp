#include "game_test.h"

#include <fstream>

#include "game/game.h"
#include "graphics/tilelayer.h"
#include "graphics/tilesetpack.h"
#include "raylib.h"

using namespace Brutal;

TEST_F(GameTest, TestGameObject) {
    // Game& game = Game::Get();

    // game.Setup(640, 480);

    // game.CreateLevel();
    // game.level->LoadSprite("testdata/player.png", 0);

    // Test off screen (Blank)
    // game.view_screen.x = 100;
    // game.view_screen.y = 100;

    // Test view screen off -200, -200, gameobject should be right and lower from 0,0
    // game.view_screen.x = -200;
    // game.view_screen.y = -200;

    // game.MainLoop();

    // game.Cleanup();
}

TEST_F(GameTest, TestTileLayer) {
    Game& game = Game::Get();

    game.Setup(640, 480);

    game.CreateLevel();

    EXPECT_TRUE(game.level != nullptr);

    std::ifstream test_json("testdata/level.json");

    json json_data = json::parse(test_json);

    game.level->Deserialize(json_data);

    // Test off screen, should clip left and top portion of tile map
    game.view_screen.x = 100;
    game.view_screen.y = 100;

    // Test view screen off -200, -200, tile should start right and lower
    // game.view_screen.x = -200;
    // game.view_screen.y = -200;

    game.MainLoop();

    game.Cleanup();
}