#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

typedef struct {
	int size;
	int scale;
	sf::Texture* texture;
	std::vector<sf::Sprite> tiles;
} TileMap;

TileMap CreateTileMap(std::string texture_path, int scale, int size);
void DestructTileMap(TileMap& tile_map);
sf::Sprite CreateTileSprite(int x, int y, int scale, int size, sf::Texture* texture, int map_index);
