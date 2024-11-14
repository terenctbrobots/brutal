#include "game_test.h"

#include <fstream>

#include "UUID.h"
#include "game/game.h"
#include "game/gameobject.h"
#include "graphics/bitmap.h"
#include "graphics/sprite.h"
#include "graphics/tilelayer.h"
#include "graphics/tilesetpack.h"

using namespace Brutal;

TEST_F(GameTest, TestGameObject) {
    Game& game = Game::Get();

    game.Setup(640, 480);

    game.CreateLevel();

    std::ifstream test_json("testdata/levelgameobject.json");

    json json_data = json::parse(test_json);

    game.level->Deserialize(json_data);

    GameObject gameobject = game.level->FindGameObjectByName("Player 1");
    EXPECT_TRUE(gameobject);

    gameobject = game.level->GetGameObjectByUUID(1);
    EXPECT_TRUE(gameobject);

    EXPECT_TRUE(gameobject.HasComponent<SpriteComponent>());

    auto& sprite_component = gameobject.GetComponent<SpriteComponent>();

    EXPECT_EQ(sprite_component.width, 48);
    EXPECT_EQ(sprite_component.height, 48);

    gameobject = game.level->GetGameObjectByUUID(2);
    EXPECT_TRUE(gameobject);

    EXPECT_TRUE(gameobject.HasComponent<BitmapComponent>());

    auto& bitmap_component = gameobject.GetComponent<BitmapComponent>();
    EXPECT_TRUE(bitmap_component.image.data != NULL);

    game.MainLoop();

    game.Cleanup();
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
    game.level->MoveView({0, 0});

    // Test view screen off -200, -200, tile should start right and lower
    // game.view_screen.x = -200;
    // game.view_screen.y = -200;

    game.MainLoop();

    game.Cleanup();
}