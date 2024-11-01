#include <fstream>

#include "raylib.h"
#include "graphic_test.h"
#include "game/game.h"

class GameTest : public GraphicTest {
};


TEST_F(GameTest, TestGameObject)
{
    Game new_game = Game(640,480);

    std::shared_ptr<Level> new_level = new_game.CreateLevel(std::make_shared<Level>());

    new_game.MainLoop();
}