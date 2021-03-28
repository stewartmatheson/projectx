#pragma once

#include <SFML/Graphics.hpp>

// A map holds all data for a given tile layout within the game.
typedef struct {
    sf::IntRect bounds;
	std::vector<sf::Sprite>* tiles;
} Map;

Map* CreateMap(int tile_size, int map_height, int map_width);

void DestructMap(Map& map);

void DrawMap(sf::RenderTarget& target, Map& map);

sf::Vector2i GetTilePositionAt(Map& map, int x, int y, int tile_map_size);
