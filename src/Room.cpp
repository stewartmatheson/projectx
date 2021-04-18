#include "Room.h"

Room* CreateRoom(int map_height, int map_width, int window_width, int window_height) {
    Room* room = (Room*)malloc(sizeof(*room));
    room->bounds = sf::IntRect(0, 0, map_width, map_height);
    room->tiles = new std::vector<Tile>();
    return room;
}

void DestructRoom(Room& room) {
    delete room.tiles;
    free(&room);
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

