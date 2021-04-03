#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.h"

typedef struct {
    int x;
    int y;
    int rotation;
    int tile_map_index;
} RoomTile;

// A map holds all data for a given tile layout within the game.
typedef struct {
    sf::IntRect bounds;
	// std::vector<sf::Sprite>* tiles;
	std::vector<RoomTile>* tiles;
} Room;

Room* CreateRoom(int tile_size, int room_height, int room_width);

void DestructRoom(Room& room);

void DrawRoom(sf::RenderTarget& target, Room& room, TileMap& tile_map);

