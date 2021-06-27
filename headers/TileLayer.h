#pragma once

#include <vector>

struct MapTile {
    int x;
    int y;
    int rotation;
    int tile_map_index;
};

struct TileLayer {
    int layer_index;
    std::vector<MapTile> tiles;
};
