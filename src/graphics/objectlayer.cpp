#include "objectlayer.h"

#include "game/game.h"
#include "game/level.h"

namespace Brutal {
ObjectLayer::ObjectLayer() { layer_type_ = Layer::OBJECT; }

ObjectLayer::~ObjectLayer() {}

void ObjectLayer::Add(std::shared_ptr<GameObject> gameobject) { gameobjects_.push_front(gameobject); }

void ObjectLayer::OrganizeDraw() {
    // Game& game = Game::Get();

    // // Remove all old gameobjects that are no longer in render view
    // auto old_gameobject = drawlist_.begin();
    // while (old_gameobject != drawlist_.end()) {
    //     if ((*old_gameobject)->enabled == false || !CheckCollisionRecs(game.view_screen,
    //     (*old_gameobject)->position)) {
    //         old_gameobject = drawlist_.erase(old_gameobject);
    //     } else {
    //         old_gameobject++;
    //     }
    // }

    // // Add new game objects that are in render view
    // auto new_gameobject = gameobjects_.begin();
    // while (new_gameobject != gameobjects_.end()) {
    //     if ((*new_gameobject)->enabled == true && CheckCollisionRecs(game.view_screen, (*new_gameobject)->position))
    //     {
    //         drawlist_.push_front(*new_gameobject);
    //     }
    //     new_gameobject++;
    // }
}

void ObjectLayer::Draw() {
    // auto gameobject = drawlist_.begin();
    // while (gameobject != drawlist_.end()) {
    //     (*gameobject++)->Draw();
    // }
}

}  // namespace Brutal
