#include <fstream>

#include "raylib.h"
#include "game_test.h"
#include "game/game.h"

TEST_F(GameTest, TestGameObject)
{
    Game& game = Game::Get();

    game.Setup(640,480);

    game.CreateLevel();
    game.level->LoadSprite("testdata/player.png",0);

    game.MainLoop();

    game.Cleanup();
}