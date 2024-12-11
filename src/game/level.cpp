#include "level.h"

#include <fstream>
#include <iostream>
#include <memory>

#include "game/component.h"
#include "game/game.h"
#include "graphics/bitmap.h"
#include "graphics/objectlayer.h"
#include "graphics/sprite.h"
#include "graphics/tilelayer.h"
#include "helper.h"
#include "raygui.h"
#include "ui/button.h"
#include "ui/text.h"

namespace Brutal
{

void Level::Setup() { script_core = std::make_unique<ScriptCore>(); }

void Level::Cleanup()
{
    if (script_core)
    {
        script_core->Cleanup();
        script_core = nullptr;
    }

    auto sprite_view = registry_.view<SpriteComponent>();

    for (auto entity : sprite_view)
    {
        GameObject gameObject = {entity, this};

        gameObject.RemoveComponent<SpriteComponent>();
    }

    auto bitmap_view = registry_.view<BitmapComponent>();

    for (auto entity : bitmap_view)
    {
        GameObject gameObject = {entity, this};
        
        gameObject.RemoveComponent<BitmapComponent>();
    }

    gameobject_map_.clear();
    registry_.clear();
}

GameObject Level::CreateGameObject(std::string const& name) { return CreateGameObjectWithUUID(UUID(), name); }

GameObject Level::CreateGameObjectWithUUID(UUID uuid, std::string const& name)
{
    GameObject gameobject = {registry_.create(), this};
    gameobject.AddComponent<IDComponent>(uuid);
    gameobject.AddComponent<Rectangle>();
    auto& tag = gameobject.AddComponent<TagComponent>();
    tag.m_Tag = name.empty() ? "GameObject" : name;

    gameobject_map_[uuid] = gameobject;

    return gameobject;
}

void Level::DestroyGameObject(GameObject gameobject)
{
    if (gameobject.HasComponent<SpriteComponent>())
    {
        gameobject.RemoveComponent<SpriteComponent>();
    }

    if (gameobject.HasComponent<BitmapComponent>())
    {
        gameobject.RemoveComponent<BitmapComponent>();
    }
    gameobject_map_.erase(gameobject.GetUUID());
    registry_.destroy(gameobject);
}

GameObject Level::FindGameObjectByName(std::string_view name)
{
    auto view = registry_.view<TagComponent>();
    for (auto gameobject : view)
    {
        TagComponent const& tag_component = view.get<TagComponent>(gameobject);
        if (tag_component.m_Tag == name)
        {
            return GameObject{gameobject, this};
        }
    }

    return {};
}

GameObject Level::GetGameObjectByUUID(UUID uuid)
{
    if (gameobject_map_.find(uuid) != gameobject_map_.end())
    {
        return {gameobject_map_.at(uuid), this};
    }

    return {};
}

void Level::UpdateView(Rectangle const& rectangle)
{
    view_ = rectangle;
    view_updated_ = true;
}

void Level::MoveView(Vector2 const& position)
{
    view_.x = position.x;
    view_.y = position.y;
    view_updated_ = true;
}

int Level::MainLoop()
{
#ifndef NOUNIT
    char* delay_string = std::getenv("DELAY");
    int delay_frames = 5;

    if (delay_string != NULL)
    {
        delay_frames = atoi(delay_string);
    }
    int frame_counter = 0;
    bool exit_flag = false;
#endif
    SetTargetFPS(60);

#ifndef NOUNIT
    while (!WindowShouldClose() && !exit_flag)
#else
    while (!WindowShouldClose())
#endif
    {
        if (view_updated_)
        {
            OrganizeDrawList();

            for (auto& rlayer : render_layers_)
            {
                if (rlayer->m_Enabled && rlayer->GetLayerType() == Layer::TILE)
                {
                    std::static_pointer_cast<TileLayer>(rlayer)->OrganizeDraw();
                }
            }
            view_updated_ = false;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (auto& rlayer : render_layers_)
        {
            if (rlayer->m_Enabled)
            {
                rlayer->Draw();
            }
        }

        EndDrawing();

        auto script_view = registry_.view<ScriptComponent, IDComponent>();

        for (auto entity : script_view)
        {
            auto& script = script_view.get<ScriptComponent>(entity);
            auto& uuid = script_view.get<IDComponent>(entity);

            if (script.m_OnTick)
            {
                script_core->ActivateEvent({EVENT_ONTICK, uuid.m_ID});
            }
        }

        script_core->Process();

#ifndef NOUNIT
        frame_counter++;

        if (frame_counter >= delay_frames)
        {
            exit_flag = true;
        }
#endif
    }

    return 0;
}

void Level::Deserialize(json json_data)
{
    DeserializeGameObject(json_data["gameobject"]);

    for (auto& layer_data : json_data["layers"])
    {
        std::string const& layer_type = layer_data["type"];

        switch (hash(layer_type.c_str()))
        {
            case hash("tilelayer"): {
                auto new_layer = std::make_shared<TileLayer>(layer_data["width"], layer_data["height"]);
                auto new_tile_pack = std::make_shared<TileSetPack>();
                new_tile_pack->Deserialize(json_data["tilePack"]);
                new_layer->SetTileSetPack(new_tile_pack);

                json data = layer_data["data"];
                new_layer->SetLayerData(data);
                render_layers_.push_back(new_layer);
                break;
            }
            case hash("object"): {
                auto new_layer = std::make_shared<ObjectLayer>();
                size_t next_layer = render_layers_.size();
                for (auto& uuid : layer_data["data"])
                {
                    auto gameobject = GetGameObjectByUUID((int)uuid);
                    gameobject.AddComponent<LayerComponent>(next_layer);
                }
                render_layers_.push_back(new_layer);
                break;
            }
        }
    }

    script_core->Setup();
}

void Level::DeserializeGameObject(json json_data)
{
    for (auto& gameobject_data : json_data)
    {
        std::string const& name = gameobject_data["name"];
        UUID uuid = UUID(gameobject_data["uuid"]);

        GameObject gameobject = CreateGameObjectWithUUID(uuid, name);
        auto& rectangle = gameobject.GetComponent<Rectangle>();
        rectangle.x = gameobject_data["x"];
        rectangle.y = gameobject_data["y"];
        rectangle.width = gameobject_data.contains("width") ? float(gameobject_data["width"]) : 0;
        rectangle.height = gameobject_data.contains("height") ? float(gameobject_data["height"]) : 0;

        for (auto& component_data : gameobject_data["component"])
        {
            std::string const& type = component_data["type"];

            switch (hash(type.c_str()))
            {
                case hash("sprite"): {
                    auto& sprite = gameobject.AddComponent<SpriteComponent>(Sprite::Deserialize(component_data));
                    auto& rectangle = gameobject.GetComponent<Rectangle>();
                    rectangle.width = sprite.m_Width;
                    rectangle.height = sprite.m_Height;
                    break;
                }
                case hash("bitmap"):
                    gameobject.AddComponent<BitmapComponent>(Bitmap::Deserialize(component_data));
                    break;
                case hash("text"):
                    gameobject.AddComponent<TextComponent>(Text::Deserialize(component_data));
                    break;
                case hash("button"): {
                    auto& button = gameobject.AddComponent<ButtonComponent>(Button::Deserialize(component_data));
                    auto& rectangle = gameobject.GetComponent<Rectangle>();
                    rectangle.width = button.m_Width;
                    rectangle.height = button.m_Height;
                    break;
                }
                case hash("script"):
                    gameobject.AddComponent<ScriptComponent>(ScriptCore::Deserialize(component_data));
                    break;
            }
        }
#ifdef DEBUG
        spdlog::info("Level: GameObject {} succesfully created", name);
#endif
    }
}

void Level::OrganizeDrawList()
{
    Game& game = Game::Get();

    auto layer_view = registry_.view<LayerComponent>();

    for (auto entity : layer_view)
    {
        GameObject gameobject = {entity, this};
        auto& object_rect = gameobject.GetComponent<Rectangle>();
        auto& layer = gameobject.GetComponent<LayerComponent>();
        auto object_layer = std::static_pointer_cast<ObjectLayer>(render_layers_[layer.m_Layer]);

        if (!CheckCollisionRecs(game.level->View(), object_rect))
        {
            object_layer->RemoveFromDrawList(gameobject);
        }
        else
        {
            object_layer->AddToDrawList(gameobject);
        }
    }
}

template <typename T>
void Level::OnComponentRemove(T &component) {
    static_assert(sizeof(T) == 0);
}

template <>
void Level::OnComponentRemove<SpriteComponent>(SpriteComponent &component) {
    if (component.texture.id > 0) {
        UnloadTexture(component.texture);
        component.texture.id = 0;
    }
}

template <>
void Level::OnComponentRemove<BitmapComponent>(BitmapComponent &component) {
    if (component.m_Image.data != NULL) {
        UnloadImage(component.m_Image);
        component.m_Image.data = NULL;
    }

    if (component.m_Texture.id > 0) {
        UnloadTexture(component.m_Texture);
        component.m_Texture.id = 0;
    }
}

}  // namespace Brutal
