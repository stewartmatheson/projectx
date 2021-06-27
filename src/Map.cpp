#include "Map.h"
#include <fstream>

Map::Map(HouseSceneReducer &reducer) : reducer(reducer) {
    // TODO : Figure out where this goes
    // tile_layers.push_back(TileLayer{0, std::vector<MapTile>()});
}

Map::Map(HouseSceneReducer &reducer, std::string file_name) : reducer(reducer) {
    std::ifstream rf(file_name, std::ios::in | std::ios::binary);

    if (!rf) {
        std::cout << "Can't read file!" << std::endl;
        exit(1);
    }

    sf::IntRect bounds = sf::IntRect();

    rf.read(reinterpret_cast<char *>(&bounds.left), sizeof(bounds.left));
    rf.read(reinterpret_cast<char *>(&bounds.top), sizeof(bounds.top));
    rf.read(reinterpret_cast<char *>(&bounds.width), sizeof(bounds.width));
    rf.read(reinterpret_cast<char *>(&bounds.height), sizeof(bounds.height));

    reducer.SetMapBounds(bounds);

    int layer_count;
    rf.read(reinterpret_cast<char *>(&layer_count), sizeof(layer_count));

    for (auto i = 0; i < layer_count; i++) {
        int room_tile_count;
        rf.read(reinterpret_cast<char *>(&room_tile_count),
                sizeof(room_tile_count));

        std::vector<MapTile> tiles;

        for (auto i = 0; i < room_tile_count; i++) {
            MapTile tile;
            rf.read(reinterpret_cast<char *>(&tile.rotation),
                    sizeof(tile.rotation));

            rf.read(reinterpret_cast<char *>(&tile.tile_map_index),
                    sizeof(tile.tile_map_index));

            rf.read(reinterpret_cast<char *>(&tile.x), sizeof(tile.x));

            rf.read(reinterpret_cast<char *>(&tile.y), sizeof(tile.y));

            tiles.push_back(tile);
        }

        reducer.AddTileLayer(TileLayer{i, tiles});
    }

    int entity_count;
    rf.read(reinterpret_cast<char *>(&entity_count), sizeof(entity_count));
    for (auto k = 0; k < entity_count; k++) {

        EntityType type;
        rf.read(reinterpret_cast<char *>(&type), sizeof(type));

        int x;
        rf.read(reinterpret_cast<char *>(&x), sizeof(x));

        int y;
        rf.read(reinterpret_cast<char *>(&y), sizeof(y));

        std::unordered_map<EntityState, Animation> animations = {};

        reducer.AddEntity(Entity(
            type, 0, 0, x, y,
            std::weak_ptr<std::unordered_map<EntityState, Animation>>()));
    }
}

void Map::WriteToFile(std::string file_name) const {
    std::ofstream wf(file_name, std::ios::out | std::ios::binary);

    if (!wf) {
        std::cout << "Can't open file!" << std::endl;
        exit(1);
    }

    auto bounds = reducer.GetState().map_bounds;

    wf.write(reinterpret_cast<const char *>(&bounds.left), sizeof(bounds.left));
    wf.write(reinterpret_cast<const char *>(&bounds.top), sizeof(bounds.top));
    wf.write(reinterpret_cast<const char *>(&bounds.width),
             sizeof(bounds.width));
    wf.write(reinterpret_cast<const char *>(&bounds.height),
             sizeof(bounds.height));

    auto tile_layers = reducer.GetState().tile_layers;

    int size = tile_layers.size();
    wf.write(reinterpret_cast<const char *>(&size), sizeof(size));

    for (const auto &tile_layer : tile_layers) {
        int room_tile_count = tile_layer.tiles.size();
        wf.write(reinterpret_cast<const char *>(&room_tile_count),
                 sizeof(room_tile_count));

        for (const auto &t : tile_layer.tiles) {
            wf.write(reinterpret_cast<const char *>(&t.rotation),
                     sizeof(t.rotation));

            wf.write(reinterpret_cast<const char *>(&t.tile_map_index),
                     sizeof(t.tile_map_index));

            wf.write(reinterpret_cast<const char *>(&t.x), sizeof(t.x));

            wf.write(reinterpret_cast<const char *>(&t.y), sizeof(t.y));
        }
    }

    auto entities = reducer.GetState().entities;

    int entity_size = entities.size();
    wf.write(reinterpret_cast<const char *>(&entity_size), sizeof(entity_size));

    std::for_each(entities.begin(), entities.end(), [&wf](Entity entity) {
        EntityType type = entity.GetEntityType();
        // typedef std::underlying_type<EntityType>::type utype;
        // int i = static_cast<utype>(type);

        wf.write(reinterpret_cast<const char *>(&type), sizeof(type));

        int x = entity.GetTransform().x;
        wf.write(reinterpret_cast<const char *>(&x), sizeof(x));

        int y = entity.GetTransform().y;
        wf.write(reinterpret_cast<const char *>(&y), sizeof(y));
    });
}
