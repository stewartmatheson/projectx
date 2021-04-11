#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

typedef struct {
	int size;
	int scale;
	sf::Texture* texture;
	std::vector<sf::Sprite>* tiles;
} TileMap;

typedef struct {
    int x;
    int y;
    int rotation;
    int tile_map_index;
} Tile;

TileMap* CreateTileMap(std::string texture_path, int scale, int size, int cols, int rows);
void DestructTileMap(TileMap& tile_map);
sf::Sprite CreateTileSprite(int x, int y, int scale, int size, sf::Texture& texture, int map_index);
