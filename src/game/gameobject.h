#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <cstdint>
#include <entt/entt.hpp>
#include <memory>
#include <string>

#include "level.h"
#include "raylib.h"
#include "render.h"
#include "spdlog/spdlog.h"

class GameObject {
   private:
    entt::entity handle_{entt::null};
    Level* level_ = nullptr;

   protected:
    // TODO: Make this a unique_ptr, once we can serialize it
    std::shared_ptr<Render> render_;
    u_int64_t uid_;

   public:
    std::string name;
    Rectangle position;
    bool enabled = true;

    GameObject(entt::entity handle, Level* level);
    GameObject(std::string const& name);
    ~GameObject();

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
#ifdef DEBUG
        if (HasComponent<T>()) {
            spdlog::error("GameObject : Component already exists");
        }
#endif
        T& component = level_->registry_.emplace<T>(handle_, std::forward<Args>(args)...);
        //       level_->OnComponentAdded<T>(*this, component);
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

    //    int LoadSprite(std::string const& file_name);
    //    void Draw();

    operator bool() const { return handle_ != entt::null; }
    operator entt::entity() const { return handle_; }
    operator uint32_t() const { return (uint32_t)handle_; }
};

#endif