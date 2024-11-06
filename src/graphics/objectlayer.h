#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include <list>

#include "game/gameobject.h"
#include "layer.h"

namespace Graphics {
class ObjectLayer : public Layer {
   private:
    std::list<std::shared_ptr<GameObject>> gameobjects_;
    std::list<std::shared_ptr<GameObject>> drawlist_;

   public:
    ObjectLayer();
    ~ObjectLayer();

    void Add(std::shared_ptr<GameObject> gameobject);

    void OrganizeDraw() override;
    void Draw() override;
};

}  // namespace Graphics

#endif