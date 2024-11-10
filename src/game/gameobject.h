#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <memory>

#include "common.h"
#include "component.h"
#include "level.h"

namespace Brutal {

class GameObject {
   private:
    entt::entity handle_{entt::null};
    Level* level_ = nullptr;
    template <typename T>
    void OnComponentRemove(T& component);
    template <typename T>
    void OnComponentAdd(T& component);

   public:
    GameObject() = default;
    GameObject(entt::entity handle, Level* level);
    GameObject(GameObject const& other) = default;
    ~GameObject();

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
#ifdef DEBUG
        if (HasComponent<T>()) {
            spdlog::error("GameObject : Component already exists");
            abort();
        }
#endif
        T& component = level_->registry_.emplace<T>(handle_, std::forward<Args>(args)...);
        //       level_->OnComponentAdded<T>(*this, component);
        return component;
    }

    template <typename T, typename... Args>
    T& AddOrReplaceComponent(Args&&... args) {
        T& component = level_->registry_.emplace_or_replace<T>(handle_, std::forward<Args>(args)...);
        return component;
    }

    template <typename T>
    bool HasComponent() {
        return level_->registry_.any_of<T>(handle_);
    }

    template <typename T>
    T& GetComponent() {
        return level_->registry_.get<T>(handle_);
    }

    template <typename T>
    void RemoveComponent() {
        auto& component = level_->registry_.get<T>(handle_);
        OnComponentRemove<T>(component);
        std::cout << "Remove component" << std::endl;
        level_->registry_.remove<T>(handle_);
    }

    operator bool() const { return handle_ != entt::null; }
    operator entt::entity() const { return handle_; }
    operator uint32_t() const { return (uint32_t)handle_; }

    UUID GetUUID() { return GetComponent<IDComponent>().ID; }
    const std::string& GetName() { return GetComponent<TagComponent>().tag; }

    bool operator==(const GameObject& other) const { return handle_ == other.handle_ && level_ == other.level_; }

    bool operator!=(const GameObject& other) const { return !(*this == other); }
};
}  // namespace Brutal

#endif