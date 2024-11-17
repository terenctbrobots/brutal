#pragma once

#include <memory>
#include <vector>

#include "common.h"
#include "game/level.h"

namespace Brutal {

class Layer {
   protected:
    int layer_type_;

   public:
    enum LayerType { BASE = 0, OBJECT, TILE };

    bool enabled = true;

    Layer() {};
    ~Layer() {};

    int GetLayerType() { return layer_type_; }

    virtual void OrganizeDraw() {};
    virtual void Draw() = 0;
};
}  // namespace Brutal