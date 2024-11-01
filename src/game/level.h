#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include "graphics/layer.h"
#include "gameobject.h"

class Level 
{
    private:
        std::vector<std::unique_ptr<Layer>> render_layers_;

    public:

        Rectangle *view_screen;
        
        Level();
        ~Level();

        int Add(std::shared_ptr<GameObject> gameobject);
        int Remove();

        int MainLoop();
};

#endif