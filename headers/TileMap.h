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

TileMap *CreateTileMap(std::string, int, int, int, int);
void DestructTileMap(TileMap &);
sf::Sprite CreateTileSprite(int, int, int, int, sf::Texture &, int);
