#include "level.h"

#include <fstream>
#include <iostream>
#include <memory>

#include "game/component.h"
#include "graphics/bitmap.h"
#include "graphics/objectlayer.h"
#include "graphics/sprite.h"
#include "graphics/tilelayer.h"
#include "helper.h"
#include "raygui.h"
#include "ui/button.h"
#include "ui/text.h"

namespace Brutal {

constexpr size_t hash(const char* str) {
    const long long p = 131;
    const long long m = 4294967291;  // 2^32 - 5, largest 32 bit prime
    long long total = 0;
    long long current_multiplier = 1;
    for (int i = 0; str[i] != '\0'; ++i) {
        total = (total + current_multiplier * str[i]) % m;
        current_multiplier = (current_multiplier * p) % m;
    }
    return total;
}

Level::~Level() {
    auto sprite_view = registry_.view<SpriteComponent>();

    for (auto entity : sprite_view) {
        auto& sprite_component = sprite_view.get<SpriteComponent>(entity);
        if (sprite_component.texture.id > 0) {
            UnloadTexture(sprite_component.texture);
            sprite_component.texture.id = 0;
        }
    }

    auto bitmap_view = registry_.view<BitmapComponent>();

    for (auto entity : bitmap_view) {
        auto& bitmap_component = bitmap_view.get<BitmapComponent>(entity);
        if (bitmap_component.image.data != NULL) {
            UnloadImage(bitmap_component.image);
            bitmap_component.image.data = NULL;
        }

        if (bitmap_component.texture.id > 0) {
            UnloadTexture(bitmap_component.texture);
            bitmap_component.texture.id = 0;
        }
    }

    std::cout << "Level Destructor called" << std::endl;
    gameobject_map_.clear();
    registry_.clear();
}

GameObject Level::CreateGameObject(std::string const& name) { return CreateGameObjectWithUUID(UUID(), name); }

GameObject Level::CreateGameObjectWithUUID(UUID uuid, std::string const& name) {
    GameObject gameobject = {registry_.create(), this};
    gameobject.AddComponent<IDComponent>(uuid);
    gameobject.AddComponent<Rectangle>();
    auto& tag = gameobject.AddComponent<TagComponent>();
    tag.tag = name.empty() ? "GameObject" : name;

    gameobject_map_[uuid] = gameobject;

    return gameobject;
}

void Level::DestroyGameObject(GameObject gameobject) {
    if (gameobject.HasComponent<SpriteComponent>()) {
        auto& component = gameobject.GetComponent<SpriteComponent>();
        if (component.texture.id > 0) {
            UnloadTexture(component.texture);
            component.texture.id = 0;
        }
    }

    if (gameobject.HasComponent<BitmapComponent>()) {
        auto& component = gameobject.GetComponent<BitmapComponent>();
        if (component.image.data != NULL) {
            UnloadImage(component.image);
            component.image.data = NULL;
        }

        if (component.texture.id > 0) {
            UnloadTexture(component.texture);
            component.texture.id = 0;
        }
    }
    gameobject_map_.erase(gameobject.GetUUID());
    registry_.destroy(gameobject);
}

GameObject Level::FindGameObjectByName(std::string_view name) {
    auto view = registry_.view<TagComponent>();
    for (auto gameobject : view) {
        TagComponent const& tag_component = view.get<TagComponent>(gameobject);
        if (tag_component.tag == name) {
            return GameObject{gameobject, this};
        }
    }

    return {};
}

GameObject Level::GetObjectByUUID(UUID uuid) {
    if (gameobject_map_.find(uuid) != gameobject_map_.end()) {
        return {gameobject_map_.at(uuid), this};
    }

    return {};
}

//-------------------------------------------------------------------------------------------

int Level::Add(std::shared_ptr<GameObject> gameobject, u_int32_t layer) {
    auto render_layer = render_layers_[layer];

    if (render_layer->GetLayerType() == Layer::OBJECT) {
        std::static_pointer_cast<ObjectLayer>(render_layer)->Add(gameobject);
    }

    return 0;
}

int Level::MainLoop() {
#ifdef DEBUG
    char* delay_string = std::getenv("DELAY");
    int delay_frames = 5;

    if (delay_string != NULL) {
        delay_frames = atoi(delay_string);
    }
    int frame_counter = 0;
    bool exit_flag = false;
#endif
    SetTargetFPS(60);

#ifdef DEBUG
    while (!WindowShouldClose() && !exit_flag)
#else
    while (!WindowShouldClose())
#endif
    {
        for (auto olayer = render_layers_.begin(); olayer != render_layers_.end(); olayer++) {
            if ((*olayer)->enabled) {
                (*olayer)->OrganizeDraw();
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (auto rlayer = render_layers_.begin(); rlayer != render_layers_.end(); rlayer++) {
            if ((*rlayer)->enabled) {
                (*rlayer)->Draw();
            }
        }

        EndDrawing();

#ifdef DEBUG
        frame_counter++;

        if (frame_counter >= delay_frames) {
            exit_flag = true;
        }
#endif
    }

    return 0;
}

void Level::Deserialize(json json_data) {
    DeserializeGameObject(json_data["gameobject"]);

    for (auto& layer_data : json_data["layers"]) {
        std::string const& layer_type = layer_data["type"];

        if (layer_type == "tilelayer") {
            auto new_layer = std::make_shared<TileLayer>(layer_data["width"], layer_data["height"]);
            auto new_tile_pack = std::make_shared<TileSetPack>();
            new_tile_pack->Deserialize(json_data["tilePack"]);
            new_layer->SetTileSetPack(new_tile_pack);

            json data = layer_data["data"];
            new_layer->SetLayerData(data);
            render_layers_.push_back(new_layer);
        }
    }
}

void Level::DeserializeGameObject(json json_data) {
    for (auto& gameobject_data : json_data) {
        std::string const& name = gameobject_data["name"];
        UUID uuid = UUID(gameobject_data["uuid"]);

        GameObject gameobject = CreateGameObjectWithUUID(uuid, name);
        auto& rectangle = gameobject.GetComponent<Rectangle>();
        rectangle.x = gameobject_data["x"];
        rectangle.y = gameobject_data["y"];
        rectangle.width = gameobject_data["width"];
        rectangle.height = gameobject_data["height"];

        for (auto& component_data : gameobject_data["component"]) {
            std::string const& type = component_data["type"];

            switch (hash(type.c_str())) {
                case hash("sprite"):
                    gameobject.AddComponent<SpriteComponent>(Sprite::Deserialize(component_data));
                    break;
                case hash("bitmap"):
                    gameobject.AddComponent<BitmapComponent>(Bitmap::Deserialize(component_data));
                    break;
                case hash("text"):
                    gameobject.AddComponent<TextComponent>(Text::Deserialize(component_data));
                    break;
                case hash("button"):
                    gameobject.AddComponent<ButtonComponent>(Button::Deserialize(component_data));
                    break;
            }
        }
#ifdef DEBUG
        spdlog::info("Level: GameObject {} succesfully created", name);
#endif
    }
}

}  // namespace Brutal
