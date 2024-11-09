#include "gameobject.h"

#include <iostream>

#include "game/game.h"
#include "graphics/sprite.h"
#include "helper.h"

GameObject::GameObject(entt::entity handle, Level* level) : handle_(handle), level_(level) {}

GameObject::~GameObject() {
    if (HasComponent<SpriteComponent>()) {
        auto sprite_component = GetComponent<SpriteComponent>();
        if (sprite_component.texture.id > 0) {
            UnloadTexture(sprite_component.texture);
        }
    }
}

// void GameObject::Draw() {
//     if (render_ == nullptr) {
//         return;
//     }

//     Game& game = Game::Get();

//     Vector2 screen_position = {position.x - game.view_screen.x, position.y - game.view_screen.y};

//     render_->Draw(screen_position);
// }

// int GameObject::LoadSprite(std::string const& file_name) {
//     auto sprite = std::make_shared<Sprite>();
//     int return_value = sprite->Load(file_name);

//     if (return_value == Render::OK) {
//         render_ = sprite;

//         position.width = sprite->width;
//         position.height = sprite->height;
//     }

//     return return_value;
// }
