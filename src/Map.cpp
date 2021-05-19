#include <fstream>
#include "Map.h"

Map::Map(std::string file_name) {
    std::ifstream rf(file_name, std::ios::in | std::ios::binary);

    if (!rf) {
        std::cout << "Can't read file!" << std::endl;
        exit(1);
    }
   
    rf.read(reinterpret_cast<char *>(&bounds.left), sizeof (bounds.left));

    rf.read(reinterpret_cast<char *>(&bounds.top), sizeof (bounds.top));

    rf.read(reinterpret_cast<char *>(&bounds.width), sizeof (bounds.width));

    rf.read(reinterpret_cast<char *>(&bounds.height), sizeof (bounds.height));

    int layer_count;
    rf.read(
        reinterpret_cast<char *>(&layer_count), 
        sizeof(layer_count)
    );

    for(int i = 0; i < layer_count; i++) {
        int room_tile_count;
        rf.read(
            reinterpret_cast<char *>(&room_tile_count), 
            sizeof(room_tile_count)
        );

        std::vector<Tile> tiles;

        for(auto j = 0; j < room_tile_count; j++) {
            Tile tile;
            rf.read(
                reinterpret_cast<char *>(&tile.rotation), 
                sizeof (tile.rotation)
            );

            rf.read(
                reinterpret_cast<char *>(&tile.tile_map_index), 
                sizeof (tile.tile_map_index)
            );

            rf.read(
                reinterpret_cast<char *>(&tile.x), 
                sizeof (tile.x)
            );

            rf.read(
                reinterpret_cast<char *>(&tile.y), 
                sizeof (tile.y)
            );

            tiles.push_back(tile);
        }

        tile_layers.push_back(TileLayer{i, tiles});
    }

}

Map::Map(int map_file_version, int map_height, int map_width, int window_width, int window_height) : 
    map_file_version(map_file_version), 
    bounds(0, 0, map_width, map_height) {
    tile_layers.push_back(TileLayer{0, std::vector<Tile>()});
}

void Map::WriteToFile(std::string file_name) {
    std::ofstream wf(file_name, std::ios::out | std::ios::binary);

    if(!wf) {
        std::cout << "Can't open file!" << std::endl;
        exit(1);
    }

    wf.write(
        reinterpret_cast<const char *>(&bounds.left), 
        sizeof (bounds.left)
    );

    wf.write(
        reinterpret_cast<const char *>(&bounds.top), 
        sizeof (bounds.top)
    );

    wf.write(
        reinterpret_cast<const char *>(&bounds.width), 
        sizeof (bounds.width)
    );

    wf.write(
        reinterpret_cast<const char *>(&bounds.height), 
        sizeof (bounds.height)
    );



    int tile_layer_count = tile_layers.size();
    wf.write(reinterpret_cast<const char *>(&tile_layer_count), sizeof (tile_layer_count));

    for(const auto &layer : tile_layers) {
        int room_tile_count = layer.tiles.size();
        wf.write(reinterpret_cast<const char *>(&room_tile_count), sizeof (room_tile_count));

        for(const auto &t : layer.tiles) {
            wf.write(
                reinterpret_cast<const char *>(&t.rotation), 
                sizeof (t.rotation)
            );

            wf.write(
                reinterpret_cast<const char *>(&t.tile_map_index), 
                sizeof (t.tile_map_index)
            );

            wf.write(
                reinterpret_cast<const char *>(&t.x), 
                sizeof (t.x)
            );

            wf.write(
                reinterpret_cast<const char *>(&t.y), 
                sizeof (t.y)
            );
        }
    }

}

sf::IntRect Map::GetBounds () {
    return bounds;
}

std::vector<TileLayer> Map::GetTileLayers () {
    return tile_layers;
}
