#include "level.h"

#include <fstream>
#include <iostream>
#include <memory>

#include "game/component.h"
#include "graphics/objectlayer.h"
#include "graphics/tilelayer.h"
#include "json.h"

namespace Brutal {
Level::Level() {}

Level::~Level() {}

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
    gameobject_map_.erase(gameobject.GetUUID());
    registry_.destroy(gameobject);
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

int Level::LoadTileLayer(std::string const& map_filename, std::string const& tileset_filename) {
    std::ifstream map_json(map_filename);
    json parsed = json::parse(map_json);

    std::shared_ptr<TileLayer> new_layer = std::make_shared<TileLayer>(parsed["width"], parsed["height"]);

    json layer_data = parsed["layers"].at(0)["data"];  // Just grab first layer for testing
    new_layer->SetLayerData(layer_data);

    std::shared_ptr<TileSetPack> new_tile_pack = std::make_shared<TileSetPack>();
    new_tile_pack->Load(tileset_filename);

    new_layer->SetTileSetPack(new_tile_pack);

    render_layers_.push_back(new_layer);

    return 0;
}

}  // namespace Brutal
