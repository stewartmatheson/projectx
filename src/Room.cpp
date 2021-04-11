#include <fstream>
#include "Room.h"

Room* CreateRoom(int tile_size, int map_height, int map_width) {
    Room* room = (Room*)malloc(sizeof(*room));
    room->bounds = sf::IntRect(0, 0, tile_size * map_width, tile_size * map_height);
    room->tiles = new std::vector<Tile>();
    return room;
}


void DestructRoom(Room& room) {
    delete room.tiles;
    free(&room);
}

void UpdateRoom(Room& room, const sf::Event& event, Editor& editor) {
    // Question : I'm dereferencing here but these functions accept pointers. Is this the right thing to do?
    EditorUpdateResult result = UpdateEditor(editor, event);
    
    if (result.type == EditorUpdateResult::Type::Save) {
        WriteRoomToFile(room, "./assets/maps/room.bin");
    } else if (result.type == EditorUpdateResult::Type::PlaceTile) {
        room.tiles->push_back(result.tile);
    }
} 

void DrawRoom(sf::RenderTarget& target, Room& room, TileMap& tile_map) {
    for(Tile tile : *room.tiles) {
        sf::Sprite sprite_to_draw((*tile_map.tiles)[tile.tile_map_index]);
        sprite_to_draw.setRotation(tile.rotation);
        int half_tile_size = tile_map.size * tile_map.scale / 2;
        sprite_to_draw.setPosition(
            (tile.x * tile_map.size * tile_map.scale) + half_tile_size,
            (tile.y * tile_map.size * tile_map.scale) + half_tile_size
        );
        sprite_to_draw.setOrigin(tile_map.size / 2, tile_map.size / 2);
        target.draw(sprite_to_draw);
    }
}

void DrawRoom(sf::RenderTarget& target, Room& room, TileMap& tile_map, Editor& editor) {
    DrawRoom(target, room, tile_map);
    DrawEditor(target, editor, room.bounds.height, room.bounds.width);
}

void WriteRoomToFile(Room& room, std::string file_name) {
    std::ofstream wf(file_name, std::ios::out | std::ios::binary);

    if(!wf) {
        std::cout << "Can't open file!" << std::endl;
        exit(1);
    }

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.left), 
        sizeof (room.bounds.left)
    );

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.top), 
        sizeof (room.bounds.top)
    );

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.width), 
        sizeof (room.bounds.width)
    );

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.height), 
        sizeof (room.bounds.height)
    );

    int room_tile_count = room.tiles->size();
    wf.write(reinterpret_cast<const char *>(&room_tile_count), sizeof (room_tile_count));

    for(int i = 0; i < room_tile_count; i++) {
        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].rotation), 
            sizeof ((*room.tiles)[i].rotation)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].tile_map_index), 
            sizeof ((*room.tiles)[i].tile_map_index)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].x), 
            sizeof ((*room.tiles)[i].x)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].y), 
            sizeof ((*room.tiles)[i].y)
        );
    }
}

Room* ReadRoomFromFile(std::string file_name) {
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

    Room* room = (Room*)malloc(sizeof(*room));
    room->tiles = new std::vector<Tile>();
    room->bounds = sf::IntRect(bounds_left, bounds_top, bounds_width, bounds_height);


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

        room->tiles->push_back(tile);
    }

    return room;
}
