#ifndef LEVEL_H
#define LEVEL_H

#include <entt/entt.hpp>
#include <memory>
#include <vector>

#include "UUID.h"

// Forward declartion
class Layer;
class GameObject;

class Level {
   private:
    entt::registry registry_;
    std::unordered_map<UUID, entt::entity> gameobject_map_;

    std::vector<std::shared_ptr<Layer>> render_layers_;

    friend class GameObject;

   public:
    Level();
    ~Level();

    GameObject CreateGameObject(std::string const& name);
    GameObject CreateGameObjectWithUUID(UUID uuid, std::string const& name);
    void DestroyGameObject(GameObject gameobject);

    int Add(std::shared_ptr<GameObject> gameobject, uint32_t layer = 0);
    int Remove();

    int MainLoop();

    // TODO: Deprecate?
    //    int LoadSprite(std::string const& file_name, uint32_t layer);
    int LoadTileLayer(std::string const& map_file_name, std::string const& tileset_file_name);
};

#endif