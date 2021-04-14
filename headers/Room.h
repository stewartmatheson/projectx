#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Editor.h"

// A map holds all data for a given tile layout within the game.
struct Room {
    sf::IntRect bounds;
	// std::vector<sf::Sprite>* tiles;
	std::vector<Tile>* tiles;
};

Room* CreateRoom(int tile_size, int room_height, int room_width);

void DestructRoom(Room& room);

void UpdateRoom(Room& room, const sf::Event& event, Editor& editor);

void DrawRoom(sf::RenderTarget& target, Room& room, TileMap& tile_map);

void DrawRoom(sf::RenderTarget& target, Room& room, TileMap& tile_map, Editor& editor);

void WriteRoomToFile(Room& room, std::string file_name);

Room* ReadRoomFromFile(std::string file_name);

