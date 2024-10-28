#ifndef TILESETPACK_H
#define TILESETPACK_H

#include "tileset.h"

class TileSetPack 
{
    private:
        //TODO: Convert this to a unique_ptr?
        std::vector<std::shared_ptr<TileSet>> tileset_list_;

        int current_tile_id_index_ = 1;

    public:
        TileSetPack();
        ~TileSetPack();

        // TODO: Do we need a interface to add external created tilesets?
        void Add(std::shared_ptr<TileSet> tile_set);
        int Load(std::string const& file_name);
        int LoadJSON(json tile_set_json);

        int Draw(Vector2 const& position, uint tile_id);
};

#endif