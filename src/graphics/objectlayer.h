#pragma once 

#include <list>

#include "game/gameobject.h"
#include "layer.h"

namespace Brutal {
class ObjectLayer : public Layer {
   private:
   //TODO: This is slow, probably better as a vector
    std::list<GameObject> drawlist_;

   public:
    ObjectLayer();
    ~ObjectLayer();

    void AddToDrawList(GameObject const& gameobject);
    void RemoveFromDrawList(GameObject const& gameobject);

    void Draw() override;
};

}  // namespace Brutal