#include "game_test.h"

#include <fstream>

#include "game/game.h"
#include "graphics/tilelayer.h"
#include "graphics/tilesetpack.h"
#include "raylib.h"

TEST_F(GameTest, TestGameObject) {
    Game& game = Game::Get();

    game.Setup(640, 480);

    game.CreateLevel();
    game.level->LoadSprite("testdata/player.png", 0);

    game.MainLoop();

    game.Cleanup();
}

TEST_F(GameTest, TestTileLayer) {
    Game& game = Game::Get();

    game.Setup(640, 480);

    game.CreateLevel();

    game.level->LoadTileLayer("testdata/test.json", "testdata/plains.png");

    game.MainLoop();

    game.Cleanup();
}