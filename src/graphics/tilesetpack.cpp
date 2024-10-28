#include "tilesetpack.h"


TileSetPack::TileSetPack()
{

}

TileSetPack::~TileSetPack()
{

}

int TileSetPack::Load(std::string const& file_name)
{
    std::shared_ptr<TileSet> new_tileset = std::make_shared<TileSet>();
    
    int ret_value = new_tileset->Load(file_name);

    if (ret_value != Graphics::OK) 
    {
        return ret_value;
    }

    new_tileset->tile_first_id = current_tile_id_index_;
    new_tileset->tile_last_id = new_tileset->tile_first_id + new_tileset->tile_count;

    for (int i=0; i < new_tileset->tile_count; i++) 
    {
        tileset_list_.push_back(new_tileset);
    }

    current_tile_id_index_ += new_tileset->tile_count;

    return Graphics::OK;
}

void TileSetPack::Draw(Vector2 const& position, uint tile_id)
{
    if (tile_id > current_tile_id_index_) 
    {
        return;
    }

    tileset_list_[tile_id]->Draw(position, tile_id);
}