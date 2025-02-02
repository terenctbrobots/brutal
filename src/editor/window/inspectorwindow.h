#pragma once

#include <memory>
#include <vector>

#include "editor/window/window.h"

namespace Brutal
{
  class GameObject;
}

namespace Editor
{
  class Component;
}

namespace Editor
{
class InspectorWindow : public Window
{
  private:
    std::vector<std::shared_ptr<Component>> m_Components;
  public:

    void SetGameObject(Brutal::GameObject& gameObject);

    void Resize() override final;
    void Draw() override final;
    void Interact(Vector2 click) override final;
};
} // namespace Editor