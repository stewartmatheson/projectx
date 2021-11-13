#include <fstream>
#include <unordered_map>

#include "Map.h"
#include "EntityFactory.h"

MapState Map::New() { return MapState(); }

MapState Map::ReadFromFile(std::string file_name) {
    std::ifstream rf(file_name, std::ios::in | std::ios::binary);
    MapState map = MapState();

    if (!rf) {
        std::cout << "Can't read file!" << std::endl;
        exit(1);
    }

    sf::IntRect bounds = sf::IntRect();

    rf.read(reinterpret_cast<char *>(&bounds.left), sizeof(bounds.left));
    rf.read(reinterpret_cast<char *>(&bounds.top), sizeof(bounds.top));
    rf.read(reinterpret_cast<char *>(&bounds.width), sizeof(bounds.width));
    rf.read(reinterpret_cast<char *>(&bounds.height), sizeof(bounds.height));
    

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
        
        map.tile_layers.push_back(TileLayer{i, tiles});
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

        if (type == EntityType::PlayerEntity) {
            map.entities.push_back(EntityFactory::Player(sf::Vector2f(x, y)));
        } else {
            map.entities.push_back(Entity{type, 0, 0, sf::Vector2f(x, y)});
        }
    }

    int room_count;
    rf.read(reinterpret_cast<char *>(&room_count), sizeof(room_count));
    for (auto k = 0; k < room_count; k++) {

        int left;
        rf.read(reinterpret_cast<char *>(&left), sizeof(left));

        int top;
        rf.read(reinterpret_cast<char *>(&top), sizeof(top));

        int height;
        rf.read(reinterpret_cast<char *>(&height), sizeof(height));

        int width;
        rf.read(reinterpret_cast<char *>(&width), sizeof(width));

        map.rooms.push_back(sf::IntRect(left, top, width, height));
    }

    return map;
}

void Map::WriteToFile(std::string file_name, MapState state) {
    std::ofstream wf(file_name, std::ios::out | std::ios::binary);

    if (!wf) {
        std::cout << "Can't open file!" << std::endl;
        exit(1);
    }


    auto map_bounds = state.bounds;

    wf.write(reinterpret_cast<const char *>(&map_bounds.left), sizeof(map_bounds.left));
    wf.write(reinterpret_cast<const char *>(&map_bounds.top), sizeof(map_bounds.top));
    wf.write(reinterpret_cast<const char *>(&map_bounds.width),
             sizeof(map_bounds.width));
    wf.write(reinterpret_cast<const char *>(&map_bounds.height),
             sizeof(map_bounds.height));


    int size = state.tile_layers.size();
    wf.write(reinterpret_cast<const char *>(&size), sizeof(size));

    for (const auto &tile_layer : state.tile_layers) {
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

    auto entities = state.entities;
    int entity_size = entities.size();
    wf.write(reinterpret_cast<const char *>(&entity_size), sizeof(entity_size));

    std::for_each(entities.begin(), entities.end(), [&wf](Entity entity) {
        EntityType type = entity.type;
        wf.write(reinterpret_cast<const char *>(&type), sizeof(type));

        int x = entity.transform.x;
        wf.write(reinterpret_cast<const char *>(&x), sizeof(x));

        int y = entity.transform.y;
        wf.write(reinterpret_cast<const char *>(&y), sizeof(y));
    });

    auto rooms = state.rooms;
    int room_size = rooms.size();
    wf.write(reinterpret_cast<const char *>(&room_size), sizeof(room_size));
    for (auto room : state.rooms) {
        wf.write(reinterpret_cast<const char *>(&room.left), sizeof(room.left));
        wf.write(reinterpret_cast<const char *>(&room.top), sizeof(room.top));
        wf.write(reinterpret_cast<const char *>(&room.height), sizeof(room.height));
        wf.write(reinterpret_cast<const char *>(&room.width), sizeof(room.width));
    }
}


int Map::GetSpriteSize() { return 16; }
