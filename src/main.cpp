#include "game/game.h"
#include "raylib.h"

int main(void)
{
    // Turn off all raylib logging, except error messages
    SetTraceLogLevel(LOG_ERROR);
    spdlog::info("Turning off all raylib logs except errors");

    Brutal::Game &game = Brutal::Game::Get();

    game.Setup(800, 600);

    game.CreateLevel();

    game.MainLoop();

    game.Cleanup();

    return 0;
}