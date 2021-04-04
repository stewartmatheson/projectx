#include "Room.h"

Room* CreateRoom(int tile_size, int map_height, int map_width) {
    Room* room = (Room*)malloc(sizeof(*room));
    room->bounds = sf::IntRect(0, 0, tile_size * map_width, tile_size * map_height);
    room->tiles = new std::vector<RoomTile>();
    return room;
}

void DestructRoom(Room& map) { }

void DrawRoom(sf::RenderTarget& target, Room& room, TileMap& tile_map) {
    for(RoomTile room_tile : *room.tiles) {
        sf::Sprite sprite_to_draw((*tile_map.tiles)[room_tile.tile_map_index]);
        sprite_to_draw.setRotation(room_tile.rotation);
        sprite_to_draw.setPosition(
            room_tile.x * tile_map.size * tile_map.scale,
            room_tile.y * tile_map.size * tile_map.scale
        );
        target.draw(sprite_to_draw);
    }
}

