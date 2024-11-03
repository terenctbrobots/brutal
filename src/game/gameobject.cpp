#include "gameobject.h"

#include <iostream>

#include "game/game.h"
#include "graphics/sprite.h"
#include "helper.h"

GameObject::GameObject(std::string const& name) { uid_ = GetNextUid(); }

GameObject::~GameObject() {}

int GameObject::LoadSprite(std::string const& file_name) {
    auto sprite = std::make_shared<Sprite>();
    int return_value = sprite->Load(file_name);

    if (return_value == Graphics::OK) {
        graphics_ = sprite;

        position.width = sprite->width;
        position.height = sprite->height;
    }

    return return_value;
}

void GameObject::Draw() {
    if (graphics_ == nullptr) {
        return;
    }

    Game& game = Game::Get();

    Vector2 screen_position = {position.x - game.view_screen.x,
                               position.y - game.view_screen.y};

    graphics_->Draw(screen_position);
}