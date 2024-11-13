#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <vector>

#include "UUID.h"
#include "common.h"

namespace Brutal {
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
    Level() = default;
    ~Level();

    GameObject CreateGameObject(std::string const& name);
    GameObject CreateGameObjectWithUUID(UUID uuid, std::string const& name);
    void DestroyGameObject(GameObject gameobject);

    GameObject FindGameObjectByName(std::string_view);
    GameObject GetObjectByUUID(UUID uuid);

    int Add(std::shared_ptr<GameObject> gameobject, uint32_t layer = 0);
    int Remove();

    int MainLoop();

    void Deserialize(json json_data);
    void DeserializeGameObject(json json_data);
};

}  // namespace Brutal

#endif