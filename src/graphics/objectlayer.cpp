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

void ObjectLayer::Draw() {
    Game& game = Game::Get();
    Rectangle view = game.level->View();

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
