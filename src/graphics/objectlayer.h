#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include <list>

#include "game/gameobject.h"
#include "layer.h"

namespace Brutal {
class ObjectLayer : public Layer {
   private:
    std::list<GameObject> drawlist_;

   public:
    ObjectLayer();
    ~ObjectLayer();

    void AddToDrawList(GameObject const& gameobject);
    void RemoveFromDrawList(GameObject const& gameobject);

    void Draw() override;
};

}  // namespace Brutal

#endif