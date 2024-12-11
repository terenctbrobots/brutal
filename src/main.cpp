#include "raylib.h"
#include "game/game.h"

int main(void)
{
    Brutal::Game& game = Brutal::Game::Get();

    game.Setup(800,600);

    game.CreateLevel();

    game.MainLoop();

    game.Cleanup();

    return 0;
}