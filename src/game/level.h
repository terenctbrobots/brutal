#pragma once 

#include <memory>
#include <vector>

#include "UUID.h"
#include "common.h"
#include "raylib.h"
#include "script/scriptcore.h"
#include "editor/editor.h"


namespace Brutal {
// Forward declartion
class Layer;
class GameObject;

class Level {
   private:
    entt::registry registry_;
    std::unordered_map<UUID, entt::entity> gameobject_map_;

    // TODO: This looks it could be a unique_ptr
    std::vector<std::shared_ptr<Layer>> render_layers_;

    Rectangle view_;
    bool view_updated_ = true;

    void OrganizeDrawList();

    friend class GameObject;
    friend class ScriptCore;
    friend class APIGlobal;

   public:
    Level() = default;
    ~Level() = default;

    void Setup(float width, float height);
    void Cleanup();

    std::unique_ptr<ScriptCore> m_ScriptCore;
    std::unique_ptr<Editor::Editor> m_Editor;

    bool m_EditorToggle = false;

    GameObject CreateGameObject(std::string const& name);
    GameObject CreateGameObjectWithUUID(UUID uuid, std::string const& name);
    void DestroyGameObject(GameObject gameobject);

    GameObject FindGameObjectByName(std::string_view);
    GameObject GetGameObjectByUUID(UUID uuid);

    int Remove();

    void UpdateView(Rectangle const& rectangle);
    void MoveView(Vector2 const& position);
    float Width() { return view_.width; };
    float Height() { return view_.height; };
    Rectangle& View() { return view_; }

    int MainLoop();

    void Deserialize(json json_data);
    void DeserializeGameObject(json json_data);

    // GameObject 
    template <typename T>
    void OnComponentRemove(T& component);

};

}  // namespace Brutal