#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include "gameobject.h"

// Forward declartion for Layer
class Layer;

class Level 
{
    private:
        std::vector<std::shared_ptr<Layer>> render_layers_;

    public:        
        Level();
        ~Level();

        int Add(std::shared_ptr<GameObject> gameobject, uint32_t layer = 0);
        int Remove();

        int MainLoop();

        //TODO: Deprecate?
        int LoadSprite(std::string const& file_name, uint32_t layer);
};

#endif