#include <fstream>
#include "Room.h"

Room::Room(std::string file_name) {
    std::ifstream rf(file_name, std::ios::in | std::ios::binary);

    if (!rf) {
        std::cout << "Can't read file!" << std::endl;
        exit(1);
    }
   

    int bounds_left, bounds_top, bounds_width, bounds_height;

    rf.read(
        reinterpret_cast<char *>(&bounds_left), 
        sizeof (bounds_left)
    );

    rf.read(
        reinterpret_cast<char *>(&bounds_top), 
        sizeof (bounds_top)
    );

    rf.read(
        reinterpret_cast<char *>(&bounds_width), 
        sizeof (bounds_width)
    );

    rf.read(
        reinterpret_cast<char *>(&bounds_height), 
        sizeof (bounds_height)
    );

    this->tiles = new std::vector<Tile>();
    this->bounds = sf::IntRect(bounds_left, bounds_top, bounds_width, bounds_height);


    int room_tile_count;
    rf.read(
        reinterpret_cast<char *>(&room_tile_count), 
        sizeof(room_tile_count)
    );


    for(int i = 0; i < room_tile_count; i++) {
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

        this->tiles->push_back(tile);
    }
}

Room::Room(int map_height, int map_width, int window_width, int window_height) {
    this->bounds = sf::IntRect(0, 0, map_width, map_height);
    this->tiles = new std::vector<Tile>();
}

Room::~Room() {
    delete tiles;
}

void Room::DrawRoom(sf::RenderTarget& target, TileMap& tile_map) {
    for(Tile tile : *tiles) {
        sf::Sprite sprite_to_draw((*tile_map.tiles)[tile.tile_map_index]);
        sprite_to_draw.setRotation(tile.rotation);
        int half_tile_size = tile_map.tileSize() / 2;
        sprite_to_draw.setPosition(
            (tile.x * tile_map.tileSize()) + half_tile_size,
            (tile.y * tile_map.tileSize()) + half_tile_size
        );
        sprite_to_draw.setOrigin(tile_map.size / 2, tile_map.size / 2);
        target.draw(sprite_to_draw);
    }
}

void Room::WriteRoomToFile(std::string file_name) {
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

    int room_tile_count = tiles->size();
    wf.write(reinterpret_cast<const char *>(&room_tile_count), sizeof (room_tile_count));

    for(int i = 0; i < room_tile_count; i++) {
        wf.write(
            reinterpret_cast<const char *>(&(*tiles)[i].rotation), 
            sizeof ((*tiles)[i].rotation)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*tiles)[i].tile_map_index), 
            sizeof ((*tiles)[i].tile_map_index)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*tiles)[i].x), 
            sizeof ((*tiles)[i].x)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*tiles)[i].y), 
            sizeof ((*tiles)[i].y)
        );
    }
}
