#include "objectlayer.h"

#include "game/game.h"
#include "game/level.h"
#include "graphics/bitmap.h"
#include "graphics/sprite.h"
#include "ui/button.h"
#include "ui/text.h"

namespace Brutal {
ObjectLayer::ObjectLayer() { layer_type_ = Layer::OBJECT; }

ObjectLayer::~ObjectLayer() {}

void ObjectLayer::AddToDrawList(GameObject const& gameobject) { drawlist_.push_back(gameobject); }

void ObjectLayer::RemoveFromDrawList(GameObject const& gameobject) { drawlist_.remove(gameobject); }

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
    Game& game = Game::Get();
    Rectangle view = game.level->GetView();

    for (auto& gameobject : drawlist_) {
        auto& rectangle = gameobject.GetComponent<Rectangle>();

        Vector2 screen_position = {rectangle.x - view.x, rectangle.y - view.y};

        if (gameobject.HasComponent<BitmapComponent>()) {
            auto& bitmap = gameobject.GetComponent<BitmapComponent>();
            Bitmap::Draw(screen_position, bitmap);
        }

        if (gameobject.HasComponent<SpriteComponent>()) {
            auto& sprite = gameobject.GetComponent<SpriteComponent>();
            Sprite::Draw(screen_position, sprite);
        }

        if (gameobject.HasComponent<ButtonComponent>()) {
            auto& button = gameobject.GetComponent<ButtonComponent>();
            Button::Draw(screen_position, button);
        }

        if (gameobject.HasComponent<TextComponent>()) {
            auto& text = gameobject.GetComponent<TextComponent>();
            Text::Draw(screen_position, text);
        }
    }
}

}  // namespace Brutal
